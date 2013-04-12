#include <QQueue>
#include <QBitArray>
#include <QDebug>
#include <qmath.h>
#include <iostream>
#include <cassert>

#include "bsalgorithm.h"
#include "bsworkflow.h"
#include "bsconfig.h"

BSAlgorithm::BSAlgorithm()
{
}

BSAction BSAlgorithm::schedule(const BSEvent &event)
{
    QList<BSAction> actions;
    if (event.eventType == BSEvent::REQUIREMENT_CANCEL_REDUCE_E1)
    {
        actions = subScheduleE1(event);
    }
    else if (event.eventType == BSEvent::REQUIREMENT_ADD_E2)
    {
        actions = subScheduleE2(event);
    }

    int maxReward = - INT_MAX;
    int chouse = -1;
    for (int i = 0; i < actions.size(); i++)
    {
        if (maxReward < actions[i].reward)
        {
            maxReward = actions[i].reward;
            chouse = i;
        }
        qDebug() << actions[i].toString();
    }

    if (!(chouse >= 0 && chouse < actions.size()))
    {
        BSAction action;
        return action;
    }
    return actions[chouse];
}

QList<BSAction> BSAlgorithm::subScheduleE1(const BSEvent &event)
{
    QList<BSAction> actions;
    BSAction ignoreAction;
    // [1] 当前顾客取消的赔偿
    ignoreAction.reward = BSConfig::Instance()->getUnitCompensatePrice()
            * event.e1Info.reqVLevel;
    // [2] 当前顾客取消无法获得标准价格
    ignoreAction.reward -= event.e1Info.reqVLevel * BSConfig::Instance()->getUnitRPrice();
    actions.append(ignoreAction);

    BSAction forkAction = forkNewInstance(event.time, event.e1Info.instanceID, event.e1Info.reqVLevel);
    actions.append(forkAction);

    return actions;
}

QList<BSAction> BSAlgorithm::subScheduleE2(const BSEvent &event)
{
    QList<BSAction> actions;

    BSAction action1;
    action1.reward = 0;
    action1.aType = BSAction::IGNORE;
    actions.append(action1);

    BSAction action2 = addResource(event.e2Info.reqVLevel, event.e2Info.extraWTP);
    actions.append(action2);

    BSAction action3 = forkNewInstance(event.time, event.e2Info.instanceID,
                                 event.e2Info.reqVLevel, event.e2Info.extraWTP);
    actions.append(action3);


    BSAction action4 = transResource(event.e2Info.reqVLevel, event.e2Info.extraWTP);
    actions.append(action4);

    return actions;
}

BSAction BSAlgorithm::addResource(int addReqVLevel, int extraWTP)
{
    BSAction action;
    action.aType = BSAction::RESOURCE_ADD_PLAN;
    int totalResPrice = addResourceTotalPrice(addReqVLevel, action.resourceAddInfo);
    if (totalResPrice != -1)
    {
        // [1] 标准费用
        action.reward = BSConfig::Instance()->getUnitRPrice() * addReqVLevel;
        // [2] 用户需要增加新的需求所愿意额外付出的费用
        action.reward += extraWTP;
        // [3] 新的需求花费的资源成本
        action.reward -= totalResPrice;
    }
    else
    {
        action.resourceAddInfo.resourceAddList.clear();
        action.reward = - INT_MAX;
        qDebug() << "BSAlgorithm::addResource: Resource is not enough for the new requirement.";
    }
    return action;
}

BSAction BSAlgorithm::transResource(int addReqVLevel, int extraWTP)
{
    BSAction action;
    action.aType = BSAction::RESOURCE_TRANS_PLAN;
    QList<BSSNode> & sNodeList = BSWorkFlow::Instance()->bsSNodeList;
    QList<BSInstance> & ins = BSWorkFlow::Instance()->bsInstanceList;
    int allSize = (int)pow(2, ins.size());
    int *cost = new int[allSize];
    memset(cost, 0, sizeof(int) * allSize);
    int minCost = INT_MAX;
    QList<int> minChouse;
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
        if (minCost > cost[i])
        {
            minCost = cost[i];
            minChouse = chouseInsList;
        }
    }
    delete[] cost;

    // [*] 转移资源所得到新收入=新需求所带来的标准收入+新需求的额外支付-这个动作带来的成本消耗
    // 从这里可以看到新的需求想要满足把其他的实例取消来满足的话，首先付的钱要足够赔付人家，才能执行这个动作
    action.reward = BSConfig::Instance()->getUnitRPrice() * addReqVLevel + extraWTP - minCost;
    int satisfyReq = 0;
    for (int i = 0; i < minChouse.size(); i++)
    {
        ResourceTransNode node;
        node.instanceID = i;
        node.qLevel = BSWorkFlow::Instance()->getRequirementQLevel(i);
        action.resourceTransInfo.resourceTransList.append(node);
        satisfyReq += node.qLevel;
    }
    // 从候选资源里选择不够的
    if (addReqVLevel - satisfyReq > 0)
    {
        for (int i = 0; i < sNodeList.size(); i++)
        {

            ResourceAddNode node;
            node.resourceType = sNodeList[i].resType;
            node.amount = sNodeList[i].unitReqQLevel * (addReqVLevel - satisfyReq);
            if (node.amount <= BSWorkFlow::Instance()->getTotalQLevel(0, node.resourceType))
            {
                action.resourceTransInfo.resourceAddList.append(node);
            }
            else
            {
                qDebug() << "BSAlgorithm::transResource: Resource is not enough for the new requirement.";
                action.reward = - INT_MAX;
                break;
            }
        }
    }

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

    int totalResPrice = addResourceTotalPrice(addReqVLevel);
    if (totalResPrice != -1)
    {
        action.aType = BSAction::FORK_INSTANCE;
        action.forkInfo.requirementID = req.customer;
        action.forkInfo.instance.instanceID = BSWorkFlow::Instance()->bsInstanceList.size();
        action.forkInfo.instance.requirementID = req.customer;
        action.forkInfo.instance.sNodePlanList = ins.sNodePlanList;

        // [1] 标准费用
        action.reward = BSConfig::Instance()->getUnitRPrice() * addReqVLevel;
        // [2] 用户需要增加新的需求所愿意额外付出的费用
        action.reward += extraWTP;
        // [3] 新的需求花费的资源成本
        action.reward -= totalResPrice;
    }
    else
    {
        qDebug() << "BSAlgorithm::forkNewInstance: Resource is not enough for the new requirement.";
        action.reward = -INT_MAX;
    }

    return action;
}

int BSAlgorithm::addResourceTotalPrice(int addReqVLevel)
{
    int sumPrice = 0;
    QList<BSSNode> & sNodeList = BSWorkFlow::Instance()->bsSNodeList;
    for (int i = 0; i < sNodeList.size(); i++)
    {
        if (BSWorkFlow::Instance()->getTotalQLevel(0, sNodeList[i].resType)
                >= addReqVLevel * sNodeList[i].unitReqQLevel)
        {
            sumPrice += BSWorkFlow::Instance()->getResourcePrice(0, sNodeList[i].resType)
                    * sNodeList[i].unitReqQLevel * addReqVLevel;
        }
        else
        {
            return -1;
        }
    }
    return sumPrice;
}

int BSAlgorithm::addResourceTotalPrice(int addReqVLevel, ResourceAddInfo & addInfo)
{
    int sumPrice = 0;
    QList<BSSNode> & sNodeList = BSWorkFlow::Instance()->bsSNodeList;
    for (int i = 0; i < sNodeList.size(); i++)
    {
        if (BSWorkFlow::Instance()->getTotalQLevel(0, sNodeList[i].resType)
                >= addReqVLevel * sNodeList[i].unitReqQLevel)
        {
            sumPrice += BSWorkFlow::Instance()->getResourcePrice(0, sNodeList[i].resType)
                    * sNodeList[i].unitReqQLevel * addReqVLevel;
            ResourceAddNode node;
            node.resourceType = sNodeList[i].resType;
            node.amount = addReqVLevel * sNodeList[i].unitReqQLevel;
            addInfo.resourceAddList.append(node);
        }
        else
        {
            return -1;
        }
    }
    return sumPrice;
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
