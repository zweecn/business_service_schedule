#include <QQueue>
#include <QBitArray>
#include <QDebug>
#include <qmath.h>
#include <iostream>
#include <cassert>
#include <cstdlib>
#include <ctime>

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
        if (maxReward < actions[i].profit)
        {
            maxReward = actions[i].profit;
            chouse = i;
        }
    }

    if (printAllAction)
    {
        qDebug() << "--------------------------------------------------------------------";
        qDebug() << "No" << "ActionType" << "ActionDetail";
        for (int i = 0; i < actions.size(); i++)
        {
            qDebug() << i << actions[i].name() << actions[i].toString();
        }
        qDebug() << "--------------------------------------------------------------------";
    }

    if (!(chouse >= 0 && chouse < actions.size()))
    {
        BSAction action;
        return action;
    }
    return actions[chouse];
}

QList<BSAction> BSAlgorithm::scheduleActions(const BSEvent &event)
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

    for (int i = 0; i < actions.size(); i++)
    {
        if (actions[i].profit == -INT_MAX)
        {
            actions.removeAt(i);
            i--;
        }
    }
    return actions;
}

QList<BSAction> BSAlgorithm::scheduleActionsWithIntMax(const BSEvent &event)
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

    return actions;
}

BSAction BSAlgorithm::ignoreSchedule(const BSEvent & event)
{
    QList<BSAction> actions = scheduleActions(event);
    if (actions.size() <= 0)
    {
        qWarning() << __FILE__ << __LINE__ << "Ignore schedule can not get actions.";
        exit(-1);
    }
    srand(time(NULL));
    int ignoreChouse = -1;
    int cancelChouse = -1;
    for (int i = 0; i < actions.size(); i++)
    {
        if (actions[i].aType == BSAction::IGNORE)
        {
            ignoreChouse = i;
            break;
        }
        else if (actions[i].aType == BSAction::CANCEL_INSTANCE)
        {
            cancelChouse = i;
        }
    }
    if (ignoreChouse != -1)
        return actions[ignoreChouse];
    if (cancelChouse == -1)
    {
        qWarning() << __FILE__ << __LINE__ << "Ignore schedule, no cancel chouse.";
        exit(-1);
    }
    return actions[cancelChouse];
}

BSAction BSAlgorithm::randomSchedule(const BSEvent & event)
{
    QList<BSAction> actions = scheduleActions(event);
    if (actions.size() <= 0)
    {
        qWarning() << __FILE__ << __LINE__ << "Random schedule can not get actions.";
        exit(-1);
    }
    srand(time(NULL) + event.eventTime);
    int chouse = rand() % actions.size();
    return actions[chouse];
}

BSAction BSAlgorithm::minCostSchedule(const BSEvent & event)
{
    QList<BSAction> actions = scheduleActions(event);
    if (actions.size() <= 0)
    {
        qWarning() << __FILE__ << __LINE__ << "MinCost schedule can not get actions.";
        exit(-1);
    }
    srand(time(NULL));
    int chouse = 0;
    int minCost = INT_MAX;
    for (int i = 0; i < actions.size(); i++)
    {
        if (minCost > actions[i].cost)
        {
            minCost = actions[i].cost;
            chouse = i;
        }
    }
    return actions[chouse];
}

BSAction BSAlgorithm::maxProfitSchedule(const BSEvent & event)
{
    QList<BSAction> actions = scheduleActions(event);
    if (actions.size() <= 0)
    {
        qWarning() << __FILE__ << __LINE__ << "MaxProfit schedule can not get actions.";
        exit(-1);
    }
    srand(time(NULL));
    int chouse = 0;
    int maxProfit = -INT_MAX;
    for (int i = 0; i < actions.size(); i++)
    {
        if (maxProfit < actions[i].profit)
        {
            maxProfit = actions[i].profit;
            chouse = i;
        }
    }
    return actions[chouse];
}

bool BSAlgorithm::recovery(BSEvent & event, BSAction & action)
{
    if (event.eventType == BSEvent::REQUIREMENT_CANCEL_REDUCE_E1)
    {
        int insID = event.e1Info.instanceID;
        int reqID = BSWorkFlow::Instance()->bsInstanceList[insID].requirementID;
        BSRequirement &req = BSWorkFlow::Instance()->bsRequirementQueue[reqID];
        req.qLevel -= event.e1Info.reqVLevel;
        if (req.qLevel <= 0)
        {
            req.qLevel = 0;
            req.setFree(false);
        }

        if (action.aType == BSAction::IGNORE)
        {
        }
        else if (action.aType == BSAction::FORK_INSTANCE)
        {
            BSWorkFlow::Instance()->bsInstanceList.append(action.forkInfo.instance);
        }
    }
    else if (event.eventType == BSEvent::REQUIREMENT_ADD_E2)
    {
        if (action.aType == BSAction::IGNORE)
        {
        }
        else if (action.aType == BSAction::RESOURCE_ADD_PLAN)
        {
            BSWorkFlow::Instance()->bsRequirementQueue[event.e2Info.instanceID].qLevel
                    += event.e2Info.reqVLevel;
            BSWorkFlow::Instance()->bsRequirementQueue[event.e2Info.instanceID].wtp
                    += event.e2Info.extraWTP;
            for (int i = 0; i < action.resourceAddInfo.resourceAddList.size(); i++)
            {
                int resType = action.resourceAddInfo.resourceAddList[i].resourceType;
                int amount = action.resourceAddInfo.resourceAddList[i].amount;
                BSWorkFlow::Instance()->reduceResource(0, resType, amount);
            }
        }
        else if (action.aType == BSAction::RESOURCE_TRANS_PLAN)
        {
            BSWorkFlow::Instance()->bsRequirementQueue[event.e2Info.instanceID].qLevel
                    += event.e2Info.reqVLevel;
            BSWorkFlow::Instance()->bsRequirementQueue[event.e2Info.instanceID].wtp
                    += event.e2Info.extraWTP;

            for (int i = 0; i < action.resourceTransInfo.resourceTransList.size(); i++)
            {
                int insID = action.resourceTransInfo.resourceTransList[i].instanceID;
                int qLevel = action.resourceTransInfo.resourceTransList[i].qLevel;
                BSWorkFlow::Instance()->reduceRequirement(insID, qLevel);
            }
            for (int i = 0; i < action.resourceTransInfo.resourceAddList.size(); i++)
            {
                int resType = action.resourceTransInfo.resourceAddList[i].resourceType;
                int amount = action.resourceTransInfo.resourceAddList[i].amount;
                BSWorkFlow::Instance()->reduceResource(0, resType, amount);
            }
        }
        else if (action.aType == BSAction::FORK_NEXT_PERIOD)
        {
            action.forkToNextPeriodInfo.nextRequirement.customer
                    = BSWorkFlow::Instance()->bsRequirementQueue.size();
            BSWorkFlow::Instance()->bsRequirementQueue.append(action.forkToNextPeriodInfo.nextRequirement);

            BSInstance ins = BSWorkFlow::Instance()->bsInstanceList[event.e2Info.instanceID];
            ins.instanceID = BSWorkFlow::Instance()->bsInstanceList.size();
            ins.requirementID = action.forkToNextPeriodInfo.nextRequirement.customer;
            BSWorkFlow::Instance()->bsInstanceList.append(ins);

            for (int i = 0; i < action.forkToNextPeriodInfo.freeResourceList.size(); i++)
            {
                int resType = action.forkToNextPeriodInfo.freeResourceList[i].resourceType;
                int amount = action.forkToNextPeriodInfo.freeResourceList[i].amount;
                BSWorkFlow::Instance()->addResource(0, resType, amount);
            }
        }
    }
    else if (event.eventType == BSEvent::REQUIREMENT_NEW_E3)
    {
        if (action.aType == BSAction::IGNORE)
        {
        }
        else if (action.aType == BSAction::FORK_INSTANCE)
        {
            event.e3Info.requirement.customer
                    = BSWorkFlow::Instance()->bsRequirementQueue.size();
            BSWorkFlow::Instance()->bsRequirementQueue.append(event.e3Info.requirement);

            BSInstance & ins = action.forkInfo.instance;
            ins.requirementID = event.e3Info.requirement.customer;
            ins.instanceID = BSWorkFlow::Instance()->bsInstanceList.size();
            BSWorkFlow::Instance()->bsInstanceList.append(ins);

        }
        else if (action.aType == BSAction::FORK_NEXT_PERIOD)
        {
            action.forkToNextPeriodInfo.nextRequirement.customer
                    = BSWorkFlow::Instance()->bsRequirementQueue.size();
            BSWorkFlow::Instance()->bsRequirementQueue.append(action.forkToNextPeriodInfo.nextRequirement);

            BSInstance ins = BSWorkFlow::Instance()->bsInstanceList[event.e3Info.instanceID];
            ins.instanceID = BSWorkFlow::Instance()->bsInstanceList.size();
            ins.requirementID = action.forkToNextPeriodInfo.nextRequirement.customer;
            BSWorkFlow::Instance()->bsInstanceList.append(ins);

            for (int i = 0; i < action.forkToNextPeriodInfo.freeResourceList.size(); i++)
            {
                int resType = action.forkToNextPeriodInfo.freeResourceList[i].resourceType;
                int amount = action.forkToNextPeriodInfo.freeResourceList[i].amount;
                BSWorkFlow::Instance()->addResource(0, resType, amount);
            }
        }
    }
    else if (event.eventType == BSEvent::RESOURCE_REDUCE_E4)
    {
        int resType = event.e4Info.resType;
        int vQLevel = event.e4Info.vQlevel;
        BSWorkFlow::Instance()->reduceResource(0, resType, vQLevel);

        if (action.aType == BSAction::IGNORE)
        {
        }
        else if (action.aType == BSAction::CANCEL_INSTANCE)
        {
            for (int i = 0; i < action.cancelInstanceInfo.instanceIDList.size(); i++)
            {
                int insID = action.cancelInstanceInfo.instanceIDList[i];
                int reqID = BSWorkFlow::Instance()->bsInstanceList[insID].requirementID;
                BSWorkFlow::Instance()->bsRequirementQueue[reqID].reset();
            }
            for (int i = 0; i < action.cancelInstanceInfo.freeResourceList.size(); i++)
            {
                int resType = action.cancelInstanceInfo.freeResourceList[i].resourceType;
                int amount = action.cancelInstanceInfo.freeResourceList[i].amount;
                BSWorkFlow::Instance()->addResource(0, resType, amount);
            }
            int resType = action.cancelInstanceInfo.resourceAdd.resourceType;
            int amount = action.cancelInstanceInfo.resourceAdd.amount;
            BSWorkFlow::Instance()->reduceResource(0, resType, amount);
        }
        else if (action.aType == BSAction::CANCEL_DELAY_NEXT_PEROID)
        {
            for (int i = 0; i < action.cancelToDelayInstanceInfo.instanceIDList.size(); i++)
            {
                int insID = action.cancelToDelayInstanceInfo.instanceIDList[i];
                int reqID = BSWorkFlow::Instance()->bsInstanceList[insID].requirementID;
                BSWorkFlow::Instance()->bsRequirementQueue[reqID].expectedPeriod = 1;
                BSWorkFlow::Instance()->bsRequirementQueue[reqID].setFree(true);
            }
            for (int i = 0; i < action.cancelToDelayInstanceInfo.freeOrNeedResourceList.size(); i++)
            {
                int resType = action.cancelToDelayInstanceInfo.freeOrNeedResourceList[i].resourceType;
                int amount = action.cancelToDelayInstanceInfo.freeOrNeedResourceList[i].amount;
                BSWorkFlow::Instance()->addResource(0, resType, amount);
            }
            int resType = action.cancelToDelayInstanceInfo.resourceAdd.resourceType;
            int amount = action.cancelToDelayInstanceInfo.resourceAdd.amount;
            BSWorkFlow::Instance()->reduceResource(0, resType, amount);
        }
    }
    else if (event.eventType == BSEvent::SERVICE_EXEC_DELAY_E5)
    {
        if (action.aType == BSAction::IGNORE)
        {
        }
        else if (action.aType == BSAction::DELAY_TO_NEXT_PEROID)
        {
            int insID = action.delayToNextPeriodInfo.instanceID;
            int reqID = BSWorkFlow::Instance()->bsInstanceList[insID].requirementID;
            BSWorkFlow::Instance()->bsRequirementQueue[reqID].expectedPeriod = 1;
            BSWorkFlow::Instance()->bsRequirementQueue[reqID].setFree(true);

            for (int i = 0; i < action.delayToNextPeriodInfo.freeResourceList.size(); i++)
            {
                int resType = action.delayToNextPeriodInfo.freeResourceList[i].resourceType;
                int amount = action.delayToNextPeriodInfo.freeResourceList[i].amount;
                BSWorkFlow::Instance()->addResource(0, resType, amount);
            }
        }
        else if (action.aType == BSAction::CANCEL_INSTANCE)
        {
            for (int i = 0; i < action.cancelInstanceInfo.instanceIDList.size(); i++)
            {
                int insID = action.cancelInstanceInfo.instanceIDList[i];
                int reqID = BSWorkFlow::Instance()->bsInstanceList[insID].requirementID;
                BSWorkFlow::Instance()->bsRequirementQueue[reqID].reset();
            }
            for (int i = 0; i < action.cancelInstanceInfo.freeResourceList.size(); i++)
            {
                int resType = action.cancelInstanceInfo.freeResourceList[i].resourceType;
                int amount = action.cancelInstanceInfo.freeResourceList[i].amount;
                BSWorkFlow::Instance()->addResource(0, resType, amount);
            }
            int resType = action.cancelInstanceInfo.resourceAdd.resourceType;
            int amount = action.cancelInstanceInfo.resourceAdd.amount;
            BSWorkFlow::Instance()->reduceResource(0, resType, amount);
        }
    }
    else if (event.eventType == BSEvent::SERVICE_EXEC_FAILED_E6)
    {
        if (action.aType == BSAction::CANCEL_INSTANCE)
        {
            for (int i = 0; i < action.cancelInstanceInfo.instanceIDList.size(); i++)
            {
                int insID = action.cancelInstanceInfo.instanceIDList[i];
                int reqID = BSWorkFlow::Instance()->bsInstanceList[insID].requirementID;
                BSWorkFlow::Instance()->bsRequirementQueue[reqID].reset();
            }
            for (int i = 0; i < action.cancelInstanceInfo.freeResourceList.size(); i++)
            {
                int resType = action.cancelInstanceInfo.freeResourceList[i].resourceType;
                int amount = action.cancelInstanceInfo.freeResourceList[i].amount;
                BSWorkFlow::Instance()->addResource(0, resType, amount);
            }
            int resType = action.cancelInstanceInfo.resourceAdd.resourceType;
            int amount = action.cancelInstanceInfo.resourceAdd.amount;
            BSWorkFlow::Instance()->reduceResource(0, resType, amount);
        }
        else if (action.aType == BSAction::RETRY_SERVICE)
        {
        }
    }

    return true;
}

QList<BSAction> BSAlgorithm::subScheduleE1(const BSEvent &event)
{
    QList<BSAction> actions;
    BSAction ignoreAction;
    // [1] 当前顾客取消的赔偿
    ignoreAction.revenue = BSConfig::Instance()->getUnitCompensatePrice()
            * event.e1Info.reqVLevel;
    // [2] 当前顾客取消无法获得标准价格
    ignoreAction.cost = event.e1Info.reqVLevel * BSConfig::Instance()->getUnitRPrice();
    ignoreAction.profit = ignoreAction.revenue - ignoreAction.cost;
    actions.append(ignoreAction);

    BSAction forkAction = forkNewInstance(event.eventTime, event.e1Info.instanceID, event.e1Info.reqVLevel);
    actions.append(forkAction);

    return actions;
}

QList<BSAction> BSAlgorithm::subScheduleE2(const BSEvent &event)
{
    QList<BSAction> actions;

    BSAction action1;
    action1.revenue = 0;
    action1.cost = 0;
    action1.profit = 0;
    action1.aType = BSAction::IGNORE;
    actions.append(action1);

    BSAction action2 = addResource(event.e2Info.reqVLevel, event.e2Info.extraWTP);
    actions.append(action2);

// Same as add resource
//    BSAction action3 = forkNewInstance(event.eventTime, event.e2Info.instanceID,
//                                 event.e2Info.reqVLevel, event.e2Info.extraWTP);
//    actions.append(action3);


    BSAction action4 = transResource(event.e2Info.reqVLevel, event.e2Info.extraWTP);
    actions.append(action4);

    BSAction action5 = forkNextPeriod(event.eventTime, event.e2Info.instanceID,
                                      event.e2Info.reqVLevel, event.e2Info.extraWTP);
    actions.append(action5);

    return actions;
}

QList<BSAction> BSAlgorithm::subScheduleE3(const BSEvent &event)
{
    QList<BSAction> actions;

    BSAction action1;
    action1.profit = 0;
    action1.cost = 0;
    action1.revenue = 0;
    action1.aType = BSAction::IGNORE;
    actions.append(action1);

    BSAction action2 = forkNewInstance(event.eventTime, event.e3Info.instanceID,
                       event.e3Info.requirement.qLevel, event.e3Info.requirement.wtp);
    actions.append(action2);

    BSAction action3 = forkNextPeriod(event.eventTime, event.e3Info.instanceID,
                   event.e3Info.requirement.qLevel, event.e3Info.requirement.wtp);
    actions.append(action3);

    return actions;
}

QList<BSAction> BSAlgorithm::subScheduleE4(const BSEvent &event)
{
    QList<BSAction> actions;
    BSAction action1 = cancelInstances(event.eventTime, event.e4Info.resType, event.e4Info.vQlevel);
    actions.append(action1);

    BSAction action2 = cancelAndDelayNextPeriod(event.eventTime, event.e4Info.resType, event.e4Info.vQlevel);
    actions.append(action2);

    if (action1.profit == -INT_MAX && action2.profit == -INT_MAX)
    {
        BSAction action3;
        action3.aType = BSAction::IGNORE;
        action3.revenue = action3.cost = action3.profit = 0;
        actions.append(action3);
    }

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
        // [1] 每个需求都因为同步结点的延时而延时，加上延迟费用
        int totalQLevel = BSWorkFlow::Instance()->getRequirementTotalQLevel(0);
        sumCost += BSConfig::Instance()->getUnitTimeDelayCost() * timeDelay * totalQLevel;
//        qDebug() << BSConfig::Instance()->getUnitTimeDelayCost()
//                 << timeDelay << totalQLevel << "All is infrunced.";
    }
    else
    {
        // [1.1] 其他需求没有因为本实例的延时而延时，所以不需要加上它们的延时费用
        int currQLevel = BSWorkFlow::Instance()->getRequirementQLevel(0, insID);
        sumCost += BSConfig::Instance()->getUnitTimeDelayCost() * timeDelay * currQLevel;
//        qDebug() << BSConfig::Instance()->getUnitTimeDelayCost()
//                 << timeDelay << currQLevel << "Curr is infrunced.";
    }
    action1.revenue = 0;
    action1.cost = sumCost;
    action1.profit = -sumCost;
    actions.append(action1);

    BSAction action2 = cancelInstance(event.eventTime, event.e5Info.instanceID);
    actions.append(action2);

    BSAction action3 = delayNextPeriod(event.eventTime, event.e5Info.instanceID);
    actions.append(action3);

    return actions;
}

QList<BSAction> BSAlgorithm::subScheduleE6(const BSEvent &event)
{
    QList<BSAction> actions;
    BSAction action1 = retryInstance(event.e6Info.instanceID, event.e6Info.sNodeID);
    actions.append(action1);

    BSAction action2 = cancelInstance(event.eventTime, event.e6Info.instanceID);
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
    int needAddRes = 0;
    QList<int> minChouse;
    for (int i = 0; i < allSize; i++)
    {
        QList<int> chouseInsList = isOne(i);
        int sumQLevel = 0;
        int sumCost = 0;
        int freeRes = 0;
        for (int j = 0; j < chouseInsList.size(); j++)
        {
            int instanceID = chouseInsList[j];
            // [1] 损失标准价格
            int standardCost = BSConfig::Instance()->getUnitRPrice()
                    * BSWorkFlow::Instance()->getRequirementQLevel(0, instanceID);
            // [2] 损失原来的额外收益wtp
            int extraWTPCost = BSWorkFlow::Instance()->getRequirementWTP(0, instanceID);
            // [3] 取消需求需要赔偿
            int reparationCost = BSConfig::Instance()->getUnitRCancelCost()
                    * BSWorkFlow::Instance()->getRequirementQLevel(0, instanceID);
            sumQLevel += BSWorkFlow::Instance()->getRequirementQLevel(0, instanceID);
            sumCost += standardCost + extraWTPCost + reparationCost;
            freeRes += BSWorkFlow::Instance()->getResourceQLevel(0, instanceID, resType); // 0
        }

        if (sumQLevel < requireVQLevel || freeRes < vQLevel - resTotalQLevel)
        {
            sumCost = INT_MAX;
        }
        cost[i] = sumCost;
        if (minCost > cost[i])
        {
            needAddRes = vQLevel - freeRes;
            minCost = cost[i];
            minChouse = chouseInsList;
        }
    }
    delete[] cost;
    // [4] 可以从候选资源里拿出一部分来，但是需要额外付钱 resTotalQLevel
    minCost += needAddRes * BSWorkFlow::Instance()->getResourcePrice(0, resType);
    action.revenue = 0;
    action.cost = minCost;
    action.profit = -minCost;
    action.cancelInstanceInfo.instanceIDList = minChouse;
    // [*] 可以释放一些没有用过的资源
    action.cancelInstanceInfo.freeResourceList = freeResource(time, minChouse, resType);
    action.cancelInstanceInfo.resourceAdd.resourceType = resType;
    action.cancelInstanceInfo.resourceAdd.amount = needAddRes;

    return action;
}

BSAction BSAlgorithm::cancelInstance(int time, int instanceID)
{
    BSAction action;
    action.aType = BSAction::CANCEL_INSTANCE;

    int sumCost = 0;
    // [1] 损失标准价格
    int standardCost = BSConfig::Instance()->getUnitRPrice()
            * BSWorkFlow::Instance()->getRequirementQLevel(0, instanceID);
    // [2] 损失原来的额外收益wtp
    int extraWTPCost = BSWorkFlow::Instance()->getRequirementWTP(0, instanceID);
    // [3] 取消需求需要赔偿
    int reparationCost = BSConfig::Instance()->getUnitRCancelCost()
            * BSWorkFlow::Instance()->getRequirementQLevel(0, instanceID);
    sumCost += standardCost + extraWTPCost + reparationCost;

    QList<int> cancelInsList;
    cancelInsList.append(instanceID);

    action.revenue = 0;
    action.cost = sumCost;
    action.profit = -sumCost;
    action.cancelInstanceInfo.instanceIDList = cancelInsList;
    // [*] 可以释放一些没有用过的资源
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
    /* 如果
     * 1. 没有同步结点
     * 2. 重试的话，下一个同步结点会受影响延迟
     * 3. 故障结点本身就是同步结点
     * 这些情况不需要重试
     */
    if (firstSyncNodeID == -1
            || firstSyncTime > ins[instanceID].sNodePlanList[firstSyncNodeID].startTime
            || 1 == BSWorkFlow::Instance()->getSNodeConcurrencyType(sNodeID))
    {
        action.profit = - INT_MAX;
    }
    else
    {
        action.revenue = 0;
        action.cost = BSWorkFlow::Instance()->getResourcePrice(0, instanceID, sNodeID);
        action.profit = action.revenue - action.cost;
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
    //[3] 需要增加新增加的需求成功执行的标准价格和额外价格
    action.revenue += BSConfig::Instance()->getUnitRPrice() * newQlevel + extraWTP;
    action.profit = action.revenue - action.cost;
    action.aType = BSAction::FORK_NEXT_PERIOD;
    action.forkToNextPeriodInfo = action.delayToNextPeriodInfo;
    return action;
}

BSAction BSAlgorithm::cancelAndDelayNextPeriod(int time, int resType, int vQLevel)
{
    BSAction action;
    action.aType = BSAction::CANCEL_DELAY_NEXT_PEROID;

    int resTotalQLevel = BSWorkFlow::Instance()->getResourceTotalQLevel(0, resType);
    if (resTotalQLevel >= vQLevel) //Add resource
    {
        qDebug() << "BSAlgorithm::cancelInstance: no need to cancel instalces.";
        return action;
    }

    int maxFreeQLevel = BSWorkFlow::Instance()->getRequirementFreeQLevel(1);

    QList<BSInstance> & ins = BSWorkFlow::Instance()->bsInstanceList;
    int allSize = (int)pow(2, ins.size());
    int *cost = new int[allSize];
    memset(cost, 0, sizeof(int) * allSize);
    int minCost = INT_MAX;
    int needAddRes = 0;
    QList<int> minChouse;
    for (int i = 0; i < allSize; i++)
    {
        QList<int> chouseInsList = isOne(i);
        int sumQLevel = 0;
        int sumCost = 0;
        int freeRes = 0;
        for (int j = 0; j < chouseInsList.size(); j++)
        {
            int instanceID = chouseInsList[j];
            // [1] 延迟需求需要赔偿
            int delayCost = BSConfig::Instance()->getUnitDelayCost()
                    * BSWorkFlow::Instance()->getRequirementQLevel(0, instanceID);
            // [2] 延迟到下一周期需要付新资源的钱
            sumQLevel += BSWorkFlow::Instance()->getRequirementQLevel(0, instanceID);
            int unitDelayResourceCost = BSWorkFlow::Instance()->getUnitRequirementResourceCost(1);
            sumCost += delayCost + sumQLevel * unitDelayResourceCost;
            int resQLevel = BSWorkFlow::Instance()->getResourceQLevel(0, instanceID, resType);
            freeRes += resQLevel;
//            qDebug() << resQLevel << freeRes; ;

        }
//        qDebug() << freeRes << vQLevel << resTotalQLevel;
        // 如果选择的示例所需要的资源大于后一个周期的最大剩余资源
        // 或 腾出来的资源不够资源减少量
        if (sumQLevel > maxFreeQLevel || freeRes < vQLevel - resTotalQLevel)
        {
            sumCost = INT_MAX;
        }
        cost[i] = sumCost;
        if (minCost > cost[i])
        {
            needAddRes = vQLevel - freeRes;
            minCost = cost[i];
            minChouse = chouseInsList;
        }
    }
    delete[] cost;
    // [4] 可以从候选资源里拿出一部分来，但是需要额外付钱
    minCost += needAddRes * BSWorkFlow::Instance()->getResourcePrice(0, resType);
    action.revenue = 0;
    action.cost = minCost;
    action.profit = - minCost;
    action.cancelToDelayInstanceInfo.instanceIDList = minChouse;
    action.cancelToDelayInstanceInfo.freeOrNeedResourceList = freeResource(time, minChouse, -1);
    action.cancelToDelayInstanceInfo.resourceAdd.resourceType = resType;
    action.cancelToDelayInstanceInfo.resourceAdd.amount = needAddRes;

    return action;
}

BSAction BSAlgorithm::delayNextPeriod(int time, int instanceID)
{
    BSAction action;
    action.aType = BSAction::DELAY_TO_NEXT_PEROID;
    BSInstance & ins = BSWorkFlow::Instance()->bsInstanceList[instanceID];
    const BSRequirement & req = BSWorkFlow::Instance()->bsRequirementQueue[ins.requirementID];
    return delayNextPeriod(time, instanceID, req);
}

BSAction BSAlgorithm::delayNextPeriod(int time, int instanceID, const BSRequirement & req)
{
    BSAction action;
    action.aType = BSAction::DELAY_TO_NEXT_PEROID;
    QList<BSSNode> & sNodeList = BSWorkFlow::Instance()->bsSNodeList;
    int sumCost = 0;
    for (int i = 0; i < sNodeList.size(); i++)
    {
        int freeRes = BSWorkFlow::Instance()->getResourceTotalQLevel(1, sNodeList[i].resType);
        if (sNodeList[i].unitReqQLevel * req.qLevel > freeRes)
        {
            action.profit = - INT_MAX;
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
    // [1] 推迟到下一个周期的赔偿
    action.cost = BSConfig::Instance()->getUnitDelayCost() * req.qLevel;
    // [2] 下一个周期需要多购买资源的费用
    action.cost += sumCost;
    action.revenue = 0;
    action.profit = action.revenue - action.cost;
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
        // [1] 标准费用
        action.revenue = BSConfig::Instance()->getUnitRPrice() * addReqVLevel;
        // [2] 用户需要增加新的需求所愿意额外付出的费用
        action.revenue += extraWTP;
        // [3] 新的需求花费的资源成本
        action.cost = totalResPrice;
        action.profit = action.revenue - action.cost;
    }
    else
    {
        action.resourceAddInfo.resourceAddList.clear();
        action.profit = - INT_MAX;
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
            // [1] 损失标准价格
            int standardCost = BSConfig::Instance()->getUnitRPrice()
                    * BSWorkFlow::Instance()->getRequirementQLevel(0, instanceID);
            // [2] 损失原来的额外收益wtp
            int extraWTPCost = BSWorkFlow::Instance()->getRequirementWTP(0, instanceID);
            // [3] 取消需求需要赔偿
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
    //action.profit = BSConfig::Instance()->getUnitRPrice() * addReqVLevel + extraWTP - minCost;
    action.revenue = BSConfig::Instance()->getUnitRPrice() * addReqVLevel + extraWTP;
    action.cost = minCost;
    action.profit = action.revenue - action.cost;
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
    // 从候选资源里选择不够的
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
                action.profit = - INT_MAX;
                action.revenue = 0;
                action.cost = - INT_MAX;
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
        action.profit = -INT_MAX;
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
        action.revenue = BSWorkFlow::Instance()->bsRequirementQueue[req].wtp;
        // [2] 新的需求的标准价格
        action.revenue += BSWorkFlow::Instance()->bsRequirementQueue[req].qLevel
                * BSConfig::Instance()->getUnitRPrice();
        // [3] 当前顾客取消的赔偿
        action.revenue += BSConfig::Instance()->getUnitCompensatePrice()
                * freeReqVLevel;
        // [4] 当前顾客取消无法获得标准价格
        action.cost = freeReqVLevel * BSConfig::Instance()->getUnitRPrice();
        action.profit = action.revenue - action.cost;
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
        action.profit = -INT_MAX;
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
        action.revenue = BSConfig::Instance()->getUnitRPrice() * addReqVLevel;
        // [2] 用户需要增加新的需求所愿意额外付出的费用
        action.revenue += extraWTP;
        // [3] 新的需求花费的资源成本
        action.cost = totalResPrice;
        action.profit = action.revenue - action.cost;
    }
    else
    {
        qDebug() << "BSAlgorithm::forkNewInstance: Resource is not enough for the new requirement.";
        action.profit = -INT_MAX;
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
