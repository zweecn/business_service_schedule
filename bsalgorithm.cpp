#include <QQueue>
#include <QBitArray>
#include <QDebug>
#include <qmath.h>
#include <iostream>

#include "bsalgorithm.h"
#include "bsworkflow.h"
#include "bsconfig.h"

struct InsWtpSta
{
    int instanceID;
    int qLevel;
    int standardPrice;
    int extraWTP;
    double val;
    bool operator < (const InsWtpSta & other) const
    {
//        return this->val < other.val;
        return this->standardPrice + this->extraWTP < other.standardPrice + other.extraWTP;
    }
};

BSAlgorithm::BSAlgorithm()
{
}

BSAction BSAlgorithm::schedule(const BSEvent &event)
{
    BSAction action;
    if (event.eventType == BSEvent::REQUIREMENT_CANCEL_REDUCE_E1)
    {
        return subScheduleE1(event);
    }
    else if (event.eventType == BSEvent::REQUIREMENT_ADD_E2)
    {
        return subScheduleE2(event);
    }

    return action;
}

BSAction BSAlgorithm::subScheduleE1(const BSEvent &event)
{
    BSAction ignoreAction;
    // [1] 当前顾客取消的赔偿
    ignoreAction.reward = BSConfig::Instance()->getUnitCompensatePrice()
            * event.e1Info.reqVLevel;
    // [2] 当前顾客取消无法获得标准价格
    ignoreAction.reward -= event.e1Info.reqVLevel * BSConfig::Instance()->getUnitRPrice();

    BSAction forkAction = forkNewInstance(event.time, event.e1Info.instanceID, event.e1Info.reqVLevel);

    if (ignoreAction.reward >= forkAction.reward)
    {
        return ignoreAction;
    }
    return forkAction;
}

BSAction BSAlgorithm::subScheduleE2(const BSEvent &event)
{
    BSAction actions[4];
    actions[0].reward = 0;
    actions[0].aType = BSAction::IGNORE;

    actions[1] = addResource(event.e2Info.reqVLevel, event.e2Info.extraWTP);

    actions[2] = forkNewInstance(event.time, event.e2Info.instanceID,
                                 event.e2Info.reqVLevel, event.e2Info.extraWTP);

    actions[3] = transResource(event.e2Info.reqVLevel, event.e2Info.extraWTP);

    int maxReward = -INT_MAX;
    int resAction = 0;
    for (int i = 0; i < 4; i++)
    {
        if (maxReward < actions[i].reward)
        {
            maxReward = actions[i].reward;
            resAction = i;
        }
    }

    return actions[resAction];
}

BSAction BSAlgorithm::addResource(int addReqVLevel, int extraWTP)
{
    BSAction resAddAction;
    resAddAction.aType = BSAction::RESOURCE_ADD_PLAN;

    QList<BSSNode> & sNodeList = BSWorkFlow::Instance()->bsSNodeList;
    QList<BSResource> & freeResourceList = BSWorkFlow::Instance()->bsResourceList;
    int totalResPrice = 0;
    for (int i = 0; i < sNodeList.size(); i++)
    {
        int totalQLevel = sNodeList[i].unitReqQLevel * addReqVLevel;
        BSResource* res = NULL;
        for (int j = 0; j < freeResourceList.size(); j++)
        {
            if (freeResourceList[j].resType == sNodeList[i].resType
                    && freeResourceList[j].totalQLevel >= totalQLevel
                    && freeResourceList[j].period == 0)
            {
                res = &freeResourceList[j];
            }
        }
        if (res != NULL)
        {
            ResourceAddNode node;
            node.resourceType = sNodeList[i].resType;
            node.amount = totalQLevel;
            resAddAction.resourceAddInfo.resourceAddList.append(node);
            totalResPrice += totalQLevel * res->price;
        }
    }
    if (resAddAction.resourceAddInfo.resourceAddList.size() != sNodeList.size())
    {
        resAddAction.resourceAddInfo.resourceAddList.clear();
        resAddAction.reward = - INT_MAX;
    }
    else
    {
        // [1] 标准费用
        resAddAction.reward = BSConfig::Instance()->getUnitRPrice() * addReqVLevel;
        // [2] 用户需要增加新的需求所愿意额外付出的费用
        resAddAction.reward += extraWTP;
        // [3] 新的需求花费的资源成本
        resAddAction.reward -= totalResPrice;
    }
    return resAddAction;
}

BSAction BSAlgorithm::transResource(int addReqVLevel, int extraWTP)
{
    BSAction action;
    action.aType = BSAction::RESOURCE_TRANS_PLAN;
//    // [1] Cal the resource needed, it should minus candidate resource
//    QList<int> needResourceList;
    QList<BSSNode> & sNodeList = BSWorkFlow::Instance()->bsSNodeList;
//    bool needResourceTransFlag = false;
//    for (int i = 0; i < sNodeList.size(); i++)
//    {
//        int needResoruce = addReqVLevel * sNodeList[i].unitReqQLevel;
//        needResourceList.append(needResoruce);
//        int candiTotalQLevel = BSWorkFlow::Instance()->getTotalQLevel(0, sNodeList[i].resType);
//        needResourceList[i] -= candiTotalQLevel;
//        if (needResourceList[i] > 0)
//        {
//            needResourceTransFlag = true;
//        }
//    }
//    // [2] need trans, then trans. otherwise do add resource
//    if (!needResourceTransFlag)
//    {
//        action.reward = - INT_MAX;
//        return action;
//    }

    QList<BSInstance> & ins = BSWorkFlow::Instance()->bsInstanceList;
    int allSize = (int)pow(2, ins.size());
    int *cost = new int[allSize];
    memset(cost, 0, sizeof(int) * allSize);
    for (int i = 0; i < allSize; i++)
    {
        QList<int> chouseInsList = isOne(i);
        int sumQLevel = 0;
        int sumCost = 0;
        for (int j = 0; j < chouseInsList.size(); j++)
        {
            BSInstance & chouseInsTmp = ins[chouseInsList[j]];
            BSRequirement & reqTmp = BSWorkFlow::Instance()->bsRequirementQueue[chouseInsTmp.requirementID];
            // [1] 损失标准价格
            int stadPrice = reqTmp.qLevel * BSConfig::Instance()->getUnitRPrice();
            // [2] 损失原来的额外收益wtp
            int wtpTmp = reqTmp.wtp;
            // [3] 取消需求需要赔偿
            int punish = reqTmp.qLevel * BSConfig::Instance()->getUnitRCancelCost();
            sumQLevel += reqTmp.qLevel;
            sumCost += stadPrice + wtpTmp + punish;
        }

        int candiReqVLevel = addReqVLevel - sumQLevel;
        if (candiReqVLevel > 0)
        {
            for (int j = 0; j < sNodeList.size(); j++)
            {
                if (BSWorkFlow::Instance()->getTotalQLevel(0, sNodeList[j].resType)
                        > sNodeList[j].unitReqQLevel * candiReqVLevel)
                {
                    // [4] 若取消的不够，还需要从候选资源里面增加，需要成本
                    sumCost += candiReqVLevel * sNodeList[j].unitReqQLevel
                            * BSWorkFlow::Instance()->getResourcePrice(0, sNodeList[j].resType);
                }
                else
                {
                    // [4.1] 候选资源不够，不能满足
                    sumCost = INT_MAX;
                    break;
                }

            }
        }
        cost[i] = sumCost;
        qDebug() << i << cost[i];
    }

    delete[] cost;

    return action;
}

BSAction BSAlgorithm::forkNewInstance(int time, int currInstanceID, int freeReqVLevel)
{
    //Fork
    BSAction action;
    action.aType = BSAction::FORK_INSTANCE;
    BSInstance & ins = BSWorkFlow::Instance()->bsInstanceList[currInstanceID];
    QList<BSSNode> & sNodeList = BSWorkFlow::Instance()->bsSNodeList;
    int beginSyncTime = 0;
    for (int i = 0; i < sNodeList.size(); i++)
    {
        if (sNodeList[i].concurrencyType == BSSNode::SYNC_NODE)
        {
            beginSyncTime = ins.sNodePlanList[i].startTime;
            break;
        }
    }
    // Begin SyncNode, can not fork instance
    if (time >= beginSyncTime)
    {
        action.reward = -INT_MAX;
        return action;
    }

    QQueue<BSRequirement> & reqQueue = BSWorkFlow::Instance()->bsRequirementQueue;
    int wtp = 0;
    int req = -1;
    for (int i = 0; i < reqQueue.size(); i++)
    {
        if (wtp < reqQueue[i].wtp && reqQueue[i].qLevel <= freeReqVLevel)
        {
            wtp = reqQueue[i].wtp && reqQueue[i].qLevel;
            req = i;
        }
    }
    if (req != -1)
    {
        action.forkInfo.requirementID = req;
        action.forkInfo.instance.instanceID = BSWorkFlow::Instance()->bsInstanceList.size();
        action.forkInfo.instance.requirementID = req;
        action.forkInfo.instance.sNodePlanList = ins.sNodePlanList;
        // [1] fork出来后新的额外支付的价格
        action.reward = BSWorkFlow::Instance()->bsRequirementQueue[req].wtp;
        // [2] 新的需求的标准价格
        action.reward += BSWorkFlow::Instance()->bsRequirementQueue[req].qLevel
                * BSConfig::Instance()->getUnitRPrice();
        // [3] 当前顾客取消的赔偿
        action.reward += BSConfig::Instance()->getUnitCompensatePrice()
                * freeReqVLevel;
        // [4] 当前顾客取消无法获得标准价格
        action.reward -= freeReqVLevel * BSConfig::Instance()->getUnitRPrice();
    }

    return action;
}

BSAction BSAlgorithm::forkNewInstance(int time, int currInstanceID, int addReqVLevel, int extraWTP)
{
    BSInstance & ins = BSWorkFlow::Instance()->bsInstanceList[currInstanceID];
    BSAction action;
    action.aType = BSAction::FORK_INSTANCE;
    QList<BSSNode> & sNodeList = BSWorkFlow::Instance()->bsSNodeList;
    int beginSyncTime = 0;
    for (int i = 0; i < sNodeList.size(); i++)
    {
        if (sNodeList[i].concurrencyType == BSSNode::SYNC_NODE)
        {
            beginSyncTime = ins.sNodePlanList[i].startTime;
            break;
        }
    }
    // Begin SyncNode, can not fork instance
    if (time >= beginSyncTime)
    {
        action.reward = -INT_MAX;
        return action;
    }

    // Contrust a new requirement
    BSRequirement req;
    req.customer = BSWorkFlow::Instance()->bsRequirementQueue.size();
    req.expectedPeriod = 0;
    req.setFree(true);
    req.qLevel = addReqVLevel;
    req.wtp = extraWTP;

    int resNodeCount = 0;
    int totalResPrice = 0;
    for (int i = 0; i < sNodeList.size(); i++)
    {
        int resType = BSWorkFlow::Instance()->bsSNodeList[i].resType;
        QList<BSResource> & resList = BSWorkFlow::Instance()->bsResourceList;
        for (int j = 0; j < resList.size(); j++)
        {
            if (resList[j].totalQLevel >= sNodeList[i].unitReqQLevel * addReqVLevel
                    && resList[j].resType == resType && resList[j].period == 0)
            {
                resNodeCount++;
                totalResPrice += resList[j].price * addReqVLevel;
            }
        }
    }
    if (resNodeCount == sNodeList.size())
    {
        action.aType = BSAction::FORK_INSTANCE;
        action.forkInfo.requirementID = req.customer;
        action.forkInfo.instance.instanceID = BSWorkFlow::Instance()->bsInstanceList.size();
        action.forkInfo.instance.requirementID = req.customer;
        action.forkInfo.instance.sNodePlanList = ins.sNodePlanList;
        // [1] fork出来后新的额外支付的价格
        action.reward = extraWTP;
        // [2] 新的需求的标准价格
        action.reward += addReqVLevel * BSConfig::Instance()->getUnitRPrice();
        // [3] 新的需求花费的资源成本
        action.reward -= totalResPrice;
    }
    else
    {
        action.reward = -INT_MAX;
    }

    return action;
}

QList<int> BSAlgorithm::isOne(int num)
{
    QList<int> res;
    int i = 0;
    while (num)
    {
        if (num & 1)
        {
            res.append(i);
        }
        num >>= 1;
        i++;
    }
    return res;
}
