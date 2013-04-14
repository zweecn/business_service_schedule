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

BSAction BSAlgorithm::schedule(const BSEvent &event, bool printAllAction)
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
    else if (event.eventType == BSEvent::REQUIREMENT_NEW_E3)
    {
        actions = subScheduleE3(event);
    }
    else if (event.eventType == BSEvent::RESOURCE_REDUCE_E4)
    {
        actions = subScheduleE4(event);
    }
    else if (event.eventType == BSEvent::SERVICE_EXEC_DELAY_E5)
    {
        actions = subScheduleE5(event);
    }
    else if (event.eventType == BSEvent::SERVICE_EXEC_FAILED_E6)
    {
        actions = subScheduleE6(event);
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
        if (printAllAction)
        {
            qDebug() << i << actions[i].toString();
        }
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
    // [1] ��ǰ�˿�ȡ�����⳥
    ignoreAction.reward = BSConfig::Instance()->getUnitCompensatePrice()
            * event.e1Info.reqVLevel;
    // [2] ��ǰ�˿�ȡ���޷���ñ�׼�۸�
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

    BSAction action5 = forkNextPeriod(event.time, event.e2Info.instanceID,
                                      event.e2Info.reqVLevel, event.e2Info.extraWTP);
    actions.append(action5);

    return actions;
}

QList<BSAction> BSAlgorithm::subScheduleE3(const BSEvent &event)
{
    QList<BSAction> actions;

    BSAction action1;
    action1.reward = 0;
    action1.aType = BSAction::IGNORE;
    actions.append(action1);

    BSAction action2 = forkNewInstance(event.time, event.e3Info.instanceID,
                       event.e3Info.requirement.qLevel, event.e3Info.requirement.wtp);
    actions.append(action2);

    BSAction action3 = forkNextPeriod(event.time, event.e3Info.instanceID,
                   event.e3Info.requirement.qLevel, event.e3Info.requirement.wtp);
    actions.append(action3);

    return actions;
}

QList<BSAction> BSAlgorithm::subScheduleE4(const BSEvent &event)
{
    QList<BSAction> actions;
    BSAction action1 = cancelInstances(event.time, event.e4Info.resType, event.e4Info.vQlevel);
    actions.append(action1);

    return actions;
}

QList<BSAction> BSAlgorithm::subScheduleE5(const BSEvent &event)
{
    QList<BSAction> actions;
    BSAction action1;
    action1.aType = BSAction::IGNORE;

    int sNodeID = event.e5Info.sNodeID;
    int insID = event.e5Info.instanceID;
    int timeDelay = event.e5Info.timeDelay;
    QList<BSInstance> & ins = BSWorkFlow::Instance()->bsInstanceList;
    QList<BSSNode> & sNodeList = BSWorkFlow::Instance()->bsSNodeList;
    int firstSyncNodeID = 0;
    int firstSyncTime = 0;
    for (int i = sNodeID; i < sNodeList.size(); i++)
    {
        if (sNodeList[i].concurrencyType == 1)
        {
            firstSyncNodeID = i;
            break;
        }
    }
    if (firstSyncNodeID > 0)
    {
        firstSyncTime = ins[insID].sNodePlanList[firstSyncNodeID-1].endTime + timeDelay;
    }
    int sumCost = 0;
    // Others are infruenced
    if (firstSyncTime > ins[insID].sNodePlanList[firstSyncNodeID].startTime)
    {
        // [1] ÿ��������Ϊͬ��������ʱ����ʱ�������ӳٷ���
        int totalQLevel = BSWorkFlow::Instance()->getRequirementTotalQLevel(0);
        sumCost += BSConfig::Instance()->getUnitTimeDelayCost() * timeDelay * totalQLevel;
        qDebug() << BSConfig::Instance()->getUnitTimeDelayCost()
                 << timeDelay << totalQLevel << "All is infrunced.";
    }
    else
    {
        // [1.1] ��������û����Ϊ��ʵ������ʱ����ʱ�����Բ���Ҫ�������ǵ���ʱ����
        int currQLevel = BSWorkFlow::Instance()->getRequirementQLevel(0, insID);
        sumCost += BSConfig::Instance()->getUnitTimeDelayCost() * timeDelay * currQLevel;
        qDebug() << BSConfig::Instance()->getUnitTimeDelayCost()
                 << timeDelay << currQLevel << "Curr is infrunced.";
    }
    action1.reward = -sumCost;
    actions.append(action1);

    BSAction action2 = cancelInstance(event.time, event.e5Info.instanceID);
    actions.append(action2);

//    BSAction action3 = delayNextPeriod(event.time, event.e5Info.instanceID);
//    actions.append(action3);

    return actions;
}

QList<BSAction> BSAlgorithm::subScheduleE6(const BSEvent &event)
{
    QList<BSAction> actions;
    BSAction action1 = retryInstance(event.e6Info.instanceID, event.e6Info.sNodeID);
    actions.append(action1);

    BSAction action2 = cancelInstance(event.time, event.e6Info.instanceID);
    actions.append(action2);
    return actions;
}

BSAction BSAlgorithm::cancelInstances(int time, int resType, int vQLevel)
{
    BSAction action;
    action.aType = BSAction::CANCEL_INSTANCE;
    int resTotalQLevel = BSWorkFlow::Instance()->getResourceTotalQLevel(0, resType);

    if (resTotalQLevel >= vQLevel) //Add resource
    {
        qDebug() << "BSAlgorithm::cancelInstance: no need to cancel instalces.";
        return action;
    }

    int requireVQLevel = ceil(((double)vQLevel - resTotalQLevel)
                                 / BSWorkFlow::Instance()->getSNodeUnitQLevel(resType));
//    qDebug() << vQLevel << resTotalQLevel
//             << BSWorkFlow::Instance()->getSNodeUnitQLevel(resType)
//             << "requireVQLevel:" << requireVQLevel;

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
            int instanceID = chouseInsList[j];
            // [1] ��ʧ��׼�۸�
            int standardCost = BSConfig::Instance()->getUnitRPrice()
                    * BSWorkFlow::Instance()->getRequirementQLevel(0, instanceID);
            // [2] ��ʧԭ���Ķ�������wtp
            int extraWTPCost = BSWorkFlow::Instance()->getRequirementWTP(0, instanceID);
            // [3] ȡ��������Ҫ�⳥
            int reparationCost = BSConfig::Instance()->getUnitRCancelCost()
                    * BSWorkFlow::Instance()->getRequirementQLevel(0, instanceID);
            sumQLevel += BSWorkFlow::Instance()->getRequirementQLevel(0, instanceID);
            sumCost += standardCost + extraWTPCost + reparationCost;
        }

        if (sumQLevel < requireVQLevel)
        {
            sumCost = INT_MAX;
        }
        cost[i] = sumCost;
        if (minCost > cost[i])
        {
            minCost = cost[i];
            minChouse = chouseInsList;
        }
    }
    delete[] cost;
    // [4] ���ԴӺ�ѡ��Դ���ó�һ��������������Ҫ���⸶Ǯ
    minCost += resTotalQLevel * BSWorkFlow::Instance()->getResourcePrice(0, resType);
    action.reward = -minCost;
    action.cancelInstanceInfo.instanceIDList = minChouse;
    // [*] �����ͷ�һЩû���ù�����Դ
    action.cancelInstanceInfo.freeResourceList = freeResource(time, minChouse, resType);

    return action;
}

BSAction BSAlgorithm::cancelInstance(int time, int instanceID)
{
    BSAction action;
    action.aType = BSAction::CANCEL_INSTANCE;

    int sumCost = 0;
    // [1] ��ʧ��׼�۸�
    int standardCost = BSConfig::Instance()->getUnitRPrice()
            * BSWorkFlow::Instance()->getRequirementQLevel(0, instanceID);
    // [2] ��ʧԭ���Ķ�������wtp
    int extraWTPCost = BSWorkFlow::Instance()->getRequirementWTP(0, instanceID);
    // [3] ȡ��������Ҫ�⳥
    int reparationCost = BSConfig::Instance()->getUnitRCancelCost()
            * BSWorkFlow::Instance()->getRequirementQLevel(0, instanceID);
    sumCost += standardCost + extraWTPCost + reparationCost;

    QList<int> cancelInsList;
    cancelInsList.append(instanceID);

    action.reward = -sumCost;
    action.cancelInstanceInfo.instanceIDList = cancelInsList;
    // [*] �����ͷ�һЩû���ù�����Դ
    action.cancelInstanceInfo.freeResourceList = freeResource(time, cancelInsList, -1);

    return action;
}

BSAction BSAlgorithm::retryInstance(int instanceID, int sNodeID)
{
    BSAction action;
    action.aType = BSAction::RETRY_SERVICE;
    QList<BSInstance> & ins = BSWorkFlow::Instance()->bsInstanceList;
    QList<BSSNode> & sNodeList = BSWorkFlow::Instance()->bsSNodeList;
    int firstSyncNodeID = -1;
    int firstSyncTime = 0;
    for (int i = sNodeID; i < sNodeList.size(); i++)
    {
        if (sNodeList[i].concurrencyType == 1)
        {
            firstSyncNodeID = i;
            break;
        }
    }
    if (firstSyncNodeID == -1)
    {
        // All is independent
    }
    else if (firstSyncNodeID == 0)
    {
        firstSyncTime = (ins[instanceID].sNodePlanList[sNodeID].endTime
                - ins[instanceID].sNodePlanList[sNodeID].startTime);
    }
    else if (firstSyncNodeID > 0)
    {
        firstSyncTime = ins[instanceID].sNodePlanList[firstSyncNodeID-1].endTime
                + (ins[instanceID].sNodePlanList[sNodeID].endTime
                - ins[instanceID].sNodePlanList[sNodeID].startTime);
    }
    /* ���
     * 1. û��ͬ�����
     * 2. ���ԵĻ�����һ��ͬ��������Ӱ���ӳ�
     * 3. ���Ͻ�㱾�����ͬ�����
     * ��Щ�������Ҫ����
     */
    if (firstSyncNodeID == -1
            || firstSyncTime > ins[instanceID].sNodePlanList[firstSyncNodeID].startTime
            || 1 == BSWorkFlow::Instance()->getSNodeConcurrencyType(sNodeID))
    {
        action.reward = - INT_MAX;
    }
    else
    {
        action.reward = BSWorkFlow::Instance()->getResourcePrice(0, instanceID, sNodeID);
    }

    action.retryInstanceInfo.instanceID = instanceID;
    action.retryInstanceInfo.sNodeID = sNodeID;
    return action;
}

BSAction BSAlgorithm::forkNextPeriod(int time, int instanceID, int newQlevel, int extraWTP)
{
    BSRequirement req;
    req.qLevel = newQlevel;
    req.wtp = extraWTP;
    req.customer = BSWorkFlow::Instance()->bsRequirementQueue.size();
    req.expectedPeriod = 1;

    BSAction action = delayNextPeriod(time, instanceID, req);
    //[3] ��Ҫ���������ӵ�����ɹ�ִ�еı�׼�۸�Ͷ���۸�
    action.reward += BSConfig::Instance()->getUnitRPrice() * newQlevel + extraWTP;
    return action;
}

BSAction BSAlgorithm::delayNextPeriod(int time, int instanceID)
{
    BSAction action;
    action.aType = BSAction::FORK_TO_NEXT_PEROID;
    BSInstance & ins = BSWorkFlow::Instance()->bsInstanceList[instanceID];
    const BSRequirement & req = BSWorkFlow::Instance()->bsRequirementQueue[ins.requirementID];
    return delayNextPeriod(time, instanceID, req);
}

BSAction BSAlgorithm::delayNextPeriod(int time, int instanceID, const BSRequirement & req)
{
    BSAction action;
    action.aType = BSAction::FORK_TO_NEXT_PEROID;
    QList<BSSNode> & sNodeList = BSWorkFlow::Instance()->bsSNodeList;
    int sumCost = 0;
    for (int i = 0; i < sNodeList.size(); i++)
    {
        int freeRes = BSWorkFlow::Instance()->getResourceTotalQLevel(1, sNodeList[i].resType);
        if (sNodeList[i].unitReqQLevel * req.qLevel > freeRes)
        {
            action.reward = - INT_MAX;
            return action;
        }
        sumCost += sNodeList[i].unitReqQLevel * req.qLevel
                * BSWorkFlow::Instance()->getResourcePrice(1, sNodeList[i].resType);
    }
    action.delayToNextPeriodInfo.instanceID = instanceID;
    action.delayToNextPeriodInfo.beforeRequirementID = req.customer;
    action.delayToNextPeriodInfo.nextRequirement = req;
    action.delayToNextPeriodInfo.nextRequirement.customer
            = BSWorkFlow::Instance()->bsRequirementQueue.size();
    action.delayToNextPeriodInfo.nextRequirement.expectedPeriod = 1;
    QList<int> insList;
    insList.append(instanceID);
    action.delayToNextPeriodInfo.freeResourceList = freeResource(time, insList, -1);
    // [1] �Ƴٵ���һ�����ڵ��⳥
    action.reward = -BSConfig::Instance()->getUnitDelayCost() * req.qLevel;
    // [2] ��һ��������Ҫ�๺����Դ�ķ���
    action.reward -= sumCost;
    return action;
}

QList<ResourceNode> BSAlgorithm::freeResource(int time, QList<int> & chouseInstance, int exceptResType)
{
    QList<ResourceNode> freeList;

    QList<BSSNode> & sNodeList = BSWorkFlow::Instance()->bsSNodeList;
    for (int i = 0; i < sNodeList.size(); i++)
    {
        int freeResType = sNodeList[i].resType;
        if (freeResType == exceptResType)
        {
            continue;
        }
        int unitReqQLevel = sNodeList[i].unitReqQLevel;
        int sumFreeRes = 0;
        for (int j = 0; j < chouseInstance.size(); j++)
        {
            int insID = chouseInstance[j];
            BSInstance & ins = BSWorkFlow::Instance()->bsInstanceList[insID];
            int startTime = ins.sNodePlanList[i].startTime;
            if (time <= startTime)
            {
                int vQLevel = BSWorkFlow::Instance()->getRequirementQLevel(0, insID);
                sumFreeRes += vQLevel * unitReqQLevel;
            }
        }
        if (sumFreeRes > 0)
        {
            ResourceNode node;
            node.resourceType = freeResType;
            node.amount = sumFreeRes;
            freeList.append(node);
        }
    }

    return freeList;
}

BSAction BSAlgorithm::addResource(int addReqVLevel, int extraWTP)
{
    BSAction action;
    action.aType = BSAction::RESOURCE_ADD_PLAN;
    int totalResPrice = addResourceTotalPrice(addReqVLevel, action.resourceAddInfo);
    if (totalResPrice != -1)
    {
        // [1] ��׼����
        action.reward = BSConfig::Instance()->getUnitRPrice() * addReqVLevel;
        // [2] �û���Ҫ�����µ�������Ը����⸶���ķ���
        action.reward += extraWTP;
        // [3] �µ����󻨷ѵ���Դ�ɱ�
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
            int instanceID = chouseInsList[j];
            // [1] ��ʧ��׼�۸�
            int standardCost = BSConfig::Instance()->getUnitRPrice()
                    * BSWorkFlow::Instance()->getRequirementQLevel(0, instanceID);
            // [2] ��ʧԭ���Ķ�������wtp
            int extraWTPCost = BSWorkFlow::Instance()->getRequirementWTP(0, instanceID);
            // [3] ȡ��������Ҫ�⳥
            int reparationCost = BSConfig::Instance()->getUnitRCancelCost()
                    * BSWorkFlow::Instance()->getRequirementQLevel(0, instanceID);
            sumQLevel += BSWorkFlow::Instance()->getRequirementQLevel(0, instanceID);
            sumCost += standardCost + extraWTPCost + reparationCost;
        }

        int candiReqVLevel = addReqVLevel - sumQLevel;
        if (candiReqVLevel > 0)
        {
            for (int j = 0; j < sNodeList.size(); j++)
            {
                if (BSWorkFlow::Instance()->getResourceTotalQLevel(0, sNodeList[j].resType)
                        > sNodeList[j].unitReqQLevel * candiReqVLevel)
                {
                    // [4] ��ȡ���Ĳ���������Ҫ�Ӻ�ѡ��Դ�������ӣ���Ҫ�ɱ�
                    sumCost += candiReqVLevel * sNodeList[j].unitReqQLevel
                            * BSWorkFlow::Instance()->getResourcePrice(0, sNodeList[j].resType);
                }
                else
                {
                    // [4.1] ��ѡ��Դ��������������
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

    // [*] ת����Դ���õ�������=�������������ı�׼����+������Ķ���֧��-������������ĳɱ�����
    // ��������Կ����µ�������Ҫ�����������ʵ��ȡ��������Ļ������ȸ���ǮҪ�㹻�⸶�˼ң�����ִ���������
    action.reward = BSConfig::Instance()->getUnitRPrice() * addReqVLevel + extraWTP - minCost;
    int satisfyReq = 0;
    for (int i = 0; i < minChouse.size(); i++)
    {
        int instanceID = minChouse[i];
        ResourceTransNode node;
        node.instanceID = instanceID;
        node.qLevel = BSWorkFlow::Instance()->getRequirementQLevel(0, instanceID);
        action.resourceTransInfo.resourceTransList.append(node);
        satisfyReq += node.qLevel;
    }
    // �Ӻ�ѡ��Դ��ѡ�񲻹���
    if (addReqVLevel - satisfyReq > 0)
    {
        for (int i = 0; i < sNodeList.size(); i++)
        {

            ResourceAddNode node;
            node.resourceType = sNodeList[i].resType;
            node.amount = sNodeList[i].unitReqQLevel * (addReqVLevel - satisfyReq);
            if (node.amount <= BSWorkFlow::Instance()->getResourceTotalQLevel(0, node.resourceType))
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
        // [1] fork�������µĶ���֧���ļ۸�
        action.reward = BSWorkFlow::Instance()->bsRequirementQueue[req].wtp;
        // [2] �µ�����ı�׼�۸�
        action.reward += BSWorkFlow::Instance()->bsRequirementQueue[req].qLevel
                * BSConfig::Instance()->getUnitRPrice();
        // [3] ��ǰ�˿�ȡ�����⳥
        action.reward += BSConfig::Instance()->getUnitCompensatePrice()
                * freeReqVLevel;
        // [4] ��ǰ�˿�ȡ���޷���ñ�׼�۸�
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

        // [1] ��׼����
        action.reward = BSConfig::Instance()->getUnitRPrice() * addReqVLevel;
        // [2] �û���Ҫ�����µ�������Ը����⸶���ķ���
        action.reward += extraWTP;
        // [3] �µ����󻨷ѵ���Դ�ɱ�
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
        if (BSWorkFlow::Instance()->getResourceTotalQLevel(0, sNodeList[i].resType)
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
        if (BSWorkFlow::Instance()->getResourceTotalQLevel(0, sNodeList[i].resType)
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
