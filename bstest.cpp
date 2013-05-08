#include <QList>
#include <QString>
#include <QDebug>
#include <engine.h>
#include <QFile>
#include <QDateTime>

#include "bstest.h"
#include "bsworkflow.h"
#include "bsevent.h"
#include "bsaction.h"
#include "bsalgorithm.h"
#include "bsconfig.h"

BSTest::BSTest()
{
    ep = engOpen(NULL);
    if (!ep)
    {   // 定义Matlab引擎指针，启动引擎；失败则返回NULL
        qDebug() << "Can't start Matlab engine!";
        exit(-1);
    }
    engSetVisible(ep, false);
}

BSTest::~BSTest()
{
    engClose(ep);
}

void BSTest::runTest1()
{
    qDebug() << "====================================================================";
    qDebug() << "BSTest::runTest1()..." << __FILE__ << __LINE__;
    BSAlgorithm alg;
    BSEvent event;
    BSAction action;

    /* Test E1 顾客需求取消/降低
     * 1. 取消的需求所腾出来的资源不够fork另一个实例
     *    或发生事件的时间在同步时间之后，只能不作为
     */
    BSConfig::Instance()->reset();
    BSWorkFlow::Instance()->reset();
    qDebug() << "====================================================================";
    qDebug() << "Test E1.1: 取消的需求所腾出来的资源不够fork另一个实例,或发生事件的时间在同步时间之后，只能不作为...";
    event.eventType = BSEvent::REQUIREMENT_CANCEL_REDUCE_E1;
    event.eventTime = 11; //Mark
    event.e1Info.instanceID = 1;
    event.e1Info.reqVLevel = 1;
    action = alg.schedule(event, true);
    qDebug() << "Test E1.1 result:";
    qDebug() << "EventType" << "EventDetail" << "ActionType" << "ActionDetail";
    qDebug() << event.name() << event.toString() << action.name() << action.toString();
    qDebug() << "--------------------------------------------------------------------";

    /* Test E1 顾客需求取消/降低
     * 2. 取消的需求所腾出来的资源够fork另一个实例,并且取消的时间在同步时间之前
     */
    BSConfig::Instance()->reset();
    BSWorkFlow::Instance()->reset();
    qDebug() << "Test E1.2: 取消的需求所腾出来的资源够fork另一个实例,并且取消的时间在同步时间之前...";
    event.eventType = BSEvent::REQUIREMENT_CANCEL_REDUCE_E1;
    event.eventTime = 1; //Mark
    event.e1Info.instanceID = 0;
    event.e1Info.reqVLevel = 3;
    action = alg.schedule(event, true);
    qDebug() << "Test E1.2 result:";
    qDebug() << "EventType" << "EventDetail" << "ActionType" << "ActionDetail";
    qDebug() << event.name() << event.toString() << action.name() << action.toString();
    qDebug() << "--------------------------------------------------------------------";
    qDebug() << "====================================================================";

    /* Test E2 顾客需求增加
     * 1. 不需要从其他资源迁移过来，候选资源就已经足够执行增加资源分配了
     */
    BSConfig::Instance()->reset();
    BSWorkFlow::Instance()->reset();
    qDebug() << "Test E2.1: 不需要从其他资源迁移过来，候选资源就已经足够执行增加资源分配了...";
    event.eventType = BSEvent::REQUIREMENT_ADD_E2;
    event.eventTime = 1;
    event.e2Info.instanceID = 2;
    event.e2Info.reqVLevel = 1; // Mark
    event.e2Info.extraWTP = 2000;
    action = alg.schedule(event, true);
    qDebug() << "Test E2.1 result:";
    qDebug() << "EventType" << "EventDetail" << "ActionType" << "ActionDetail";
    qDebug() << event.name() << event.toString() << action.name() << action.toString();
    qDebug() << "--------------------------------------------------------------------";

    /* Test E2 顾客需求增加
     * 2. 当前周期资源不够，但是下一周期候选资源足够，可以fork新实例到下一周期
     */
    BSConfig::Instance()->reset();
    BSWorkFlow::Instance()->reset();
    qDebug() << "Test E2.2: 当前周期资源不够，但是下一周期候选资源足够，可以fork新实例到下一周期...";
    event.eventType = BSEvent::REQUIREMENT_ADD_E2;
    event.eventTime = 1;
    event.e2Info.instanceID = 2;
    event.e2Info.reqVLevel = 2; // Mark
    event.e2Info.extraWTP = 2000;
    action = alg.schedule(event, true);
    qDebug() << "Test E2.2 result:";
    qDebug() << "EventType" << "EventDetail" << "ActionType" << "ActionDetail";
    qDebug() << event.name() << event.toString() << action.name() << action.toString();
    qDebug() << "--------------------------------------------------------------------";

    /* Test E2 顾客需求增加
     * 3. 当前周期资源不够，下一周期资源也不够，只能进行资源转移
     */
    BSConfig::Instance()->reset();
    BSWorkFlow::Instance()->reset();
    qDebug() << "Test E2.3: 当前周期资源不够，下一周期资源也不够，只能进行资源转移...";
    event.eventType = BSEvent::REQUIREMENT_ADD_E2;
    event.eventTime = 1;
    event.e2Info.instanceID = 2;
    event.e2Info.reqVLevel = 2; // Mark
    event.e2Info.extraWTP = 2000;
    BSWorkFlow::Instance()->setResourceQLevel(1, 1, 0);
    action = alg.schedule(event, true);
    qDebug() << "Test E2.3 result:";
    qDebug() << "EventType" << "EventDetail" << "ActionType" << "ActionDetail";
    qDebug() << event.name() << event.toString() << action.name() << action.toString();
    qDebug() << "--------------------------------------------------------------------";
    qDebug() << "====================================================================";

    /* Test E3 新增顾客需求
     * 1. 本周期资源足够在当前周期fork新实例来满足，最好是在当前周期
     */
    BSConfig::Instance()->reset();
    BSWorkFlow::Instance()->reset();
    qDebug() << "Test E3.1: 本周期资源足够在当前周期fork新实例来满足，最好是在当前周期...";
    event.eventType = BSEvent::REQUIREMENT_NEW_E3;
    event.eventTime = 1;
    event.e3Info.instanceID = 2;
    event.e3Info.requirement.setFree(false);
    event.e3Info.requirement.customer = BSWorkFlow::Instance()->bsRequirementQueue.size();
    event.e3Info.requirement.qLevel = 1; //Mark
    event.e3Info.requirement.wtp = 1000;
    action = alg.schedule(event, true);
    qDebug() << "Test E3.1 result:";
    qDebug() << "EventType" << "EventDetail" << "ActionType" << "ActionDetail";
    qDebug() << event.name() << event.toString() << action.name() << action.toString();
    qDebug() << "--------------------------------------------------------------------";

    /* Test E3 新增顾客需求
     * 2. 本周期资源不够，不能在当前周期满足，那么就推迟到下一周期fork
     *   并且extraWTP要足够，否则不够延迟赔偿
     */
    BSConfig::Instance()->reset();
    BSWorkFlow::Instance()->reset();
    qDebug() << "Test E3.2: 本周期资源不够，不能在当前周期满足，那么就推迟到下一周期fork.并且extraWTP要足够，否则不够延迟赔偿...";
    event.eventType = BSEvent::REQUIREMENT_NEW_E3;
    event.eventTime = 1;
    event.e3Info.instanceID = 2;
    event.e3Info.requirement.setFree(false);
    event.e3Info.requirement.customer = BSWorkFlow::Instance()->bsRequirementQueue.size();
    event.e3Info.requirement.qLevel = 2; //Mark
    event.e3Info.requirement.wtp = 2000; //Mark
    action = alg.schedule(event, true);
    qDebug() << "Test E3.2 result:";
    qDebug() << "EventType" << "EventDetail" << "ActionType" << "ActionDetail";
    qDebug() << event.name() << event.toString() << action.name() << action.toString();
    qDebug() << "--------------------------------------------------------------------";

    /* Test E3 新增顾客需求
     * 3. 本周期和下一周期的资源都不够，只能不作为
     *   或者给的extraWTP不够，只能在不作为
     */
    BSConfig::Instance()->reset();
    BSWorkFlow::Instance()->reset();
    qDebug() << "Test E3.3: 本周期和下一周期的资源都不够，只能不作为.或者给的extraWTP不够，只能在不作为...";
    event.eventType = BSEvent::REQUIREMENT_NEW_E3;
    event.eventTime = 1;
    event.e3Info.instanceID = 2;
    event.e3Info.requirement.setFree(false);
    event.e3Info.requirement.customer = BSWorkFlow::Instance()->bsRequirementQueue.size();
    event.e3Info.requirement.qLevel = 3; //Mark
    event.e3Info.requirement.wtp = 1000; //Mark
    action = alg.schedule(event, true);
    qDebug() << "Test E3.3 result:";
    qDebug() << "EventType" << "EventDetail" << "ActionType" << "ActionDetail";
    qDebug() << event.name() << event.toString() << action.name() << action.toString();
    qDebug() << "--------------------------------------------------------------------";
    qDebug() << "====================================================================";

    /* Test E4 资源减少
     * 1. 下一周期的资源够迁移到下一周期的，可以取消部分当前的，迁移到下一周期
     */
    BSConfig::Instance()->reset();
    BSWorkFlow::Instance()->reset();
    qDebug() << "Test E4.1: 下一周期的资源够迁移到下一周期的，可以取消部分当前的，迁移到下一周期...";
    event.eventType = BSEvent::RESOURCE_REDUCE_E4;
    event.eventTime = 10;
    event.e4Info.resType = 2;
    event.e4Info.vQlevel = 56;
    action = alg.schedule(event, true);
    qDebug() << "Test E4.1 result:";
    qDebug() << "EventType" << "EventDetail" << "ActionType" << "ActionDetail";
    qDebug() << event.name() << event.toString() << action.name() << action.toString();
    qDebug() << "--------------------------------------------------------------------";

    /* Test E4 资源减少
     * 1. 下一周期的资源不够迁移到下一周期的，只能取消当前的
     */
    BSConfig::Instance()->reset();
    BSWorkFlow::Instance()->reset();
    qDebug() << "Test E4.2: 下一周期的资源不够迁移到下一周期的，只能取消当前的...";
    event.eventType = BSEvent::RESOURCE_REDUCE_E4;
    event.eventTime = 10;
    event.e4Info.resType = 2;
    event.e4Info.vQlevel = 56;
    BSWorkFlow::Instance()->setResourceQLevel(1, 2, 0);
    action = alg.schedule(event, true);
    qDebug() << "Test E4.2 result:";
    qDebug() << "EventType" << "EventDetail" << "ActionType" << "ActionDetail";
    qDebug() << event.name() << event.toString() << action.name() << action.toString();
    qDebug() << "--------------------------------------------------------------------";
    qDebug() << "====================================================================";

    /* Test E5 执行延时
     * 1. 延时不影响同步结点，可以执行不作为
     */
    BSConfig::Instance()->reset();
    BSWorkFlow::Instance()->reset();
    qDebug() << "Test E5.1: 延时不影响同步结点，可以执行不作为...";
    event.eventType = BSEvent::SERVICE_EXEC_DELAY_E5;
    event.eventTime = 10;
    event.e5Info.instanceID = 1;
    event.e5Info.sNodeID = 1;
    event.e5Info.timeDelay = 1; //Mark
    action = alg.schedule(event, true);
    qDebug() << "Test E5.1 result:";
    qDebug() << "EventType" << "EventDetail" << "ActionType" << "ActionDetail";
    qDebug() << event.name() << event.toString() << action.name() << action.toString();
    qDebug() << "--------------------------------------------------------------------";

    /* Test E5 执行延时
     * 2. 延时影响了同步结点，不能不作为，需要推迟当前实例
     */
    BSConfig::Instance()->reset();
    BSWorkFlow::Instance()->reset();
    qDebug() << "Test E5.2: 延时影响了同步结点，不能不作为，需要推迟当前实例...";
    event.eventType = BSEvent::SERVICE_EXEC_DELAY_E5;
    event.eventTime = 10;
    event.e5Info.instanceID = 1;
    event.e5Info.sNodeID = 1;
    event.e5Info.timeDelay = 10; //Mark
    action = alg.schedule(event, true);
    qDebug() << "Test E5.2 result:";
    qDebug() << "EventType" << "EventDetail" << "ActionType" << "ActionDetail";
    qDebug() << event.name() << event.toString() << action.name() << action.toString();
    qDebug() << "--------------------------------------------------------------------";

    /* Test E5 执行延时
     * 3. 后一个周期的资源不够，不能延迟，只能取消/或者忽略，忽略的前提是取消带来的代价更大
     */
    BSConfig::Instance()->reset();
    BSWorkFlow::Instance()->reset();
    qDebug() << "Test E5.3: 后一个周期的资源不够，不能延迟，只能取消/或者忽略，忽略的前提是取消带来的代价更大...";
    event.eventType = BSEvent::SERVICE_EXEC_DELAY_E5;
    event.eventTime = 10;
    event.e5Info.instanceID = 1;
    event.e5Info.sNodeID = 1;
    event.e5Info.timeDelay = 10; //Mark
    BSWorkFlow::Instance()->setResourceQLevel(1, 2, 0);
    action = alg.schedule(event, true);
    qDebug() << "Test E5.3 result:";
    qDebug() << "EventType" << "EventDetail" << "ActionType" << "ActionDetail";
    qDebug() << event.name() << event.toString() << action.name() << action.toString();
    qDebug() << "--------------------------------------------------------------------";
    qDebug() << "====================================================================";

    /* Test E6 执行失败
     * 1. 已经执行到同步结点，不能重试
     */
    BSConfig::Instance()->reset();
    BSWorkFlow::Instance()->reset();
    qDebug() << "Test E6.1: 已经执行到同步结点，不能重试...";
    event.eventType = BSEvent::SERVICE_EXEC_FAILED_E6;
    event.eventTime = 10;
    event.e6Info.instanceID = 1;
    event.e6Info.sNodeID = 2;
    action = alg.schedule(event, true);
    qDebug() << "Test E6.1 result:";
    qDebug() << "EventType" << "EventDetail" << "ActionType" << "ActionDetail";
    qDebug() << event.name() << event.toString() << action.name() << action.toString();
    qDebug() << "--------------------------------------------------------------------";

    /* Test E6 执行失败
     * 2. 还没有执行到同步结点，或者故障结点还不是同步结点，可以重试
     */
    BSConfig::Instance()->reset();
    BSWorkFlow::Instance()->reset();
    qDebug() << "Test E6.2: 还没有执行到同步结点，或者故障结点还不是同步结点，可以重试...";
    event.eventType = BSEvent::SERVICE_EXEC_FAILED_E6;
    event.eventTime = 1;
    event.e6Info.instanceID = 1;
    event.e6Info.sNodeID = 1; //Mark
    action = alg.schedule(event, true);
    qDebug() << "Test E6.2 result:";
    qDebug() << "EventType" << "EventDetail" << "ActionType" << "ActionDetail";
    qDebug() << event.name() << event.toString() << action.name() << action.toString();
    qDebug() << "--------------------------------------------------------------------";

    qDebug() << "BSTest::runTest1() Finished." << __FILE__ << __LINE__;
    qDebug() << "====================================================================";
}

void BSTest::runTest2()
{
    qDebug() << "====================================================================";
    qDebug() << "BSTest::runTest2()..." << __FILE__ << __LINE__;
    /*
     *   开始算法仿真，伪随机
    **/
    BSAlgorithm alg;
    BSAction action;
    currLog = QString("Test2:\n");
    QString header("Time\tEventType\tEventDetail\tActionType\tActionDetail\tRevenue\tCost\tProfit");

    // [1] 不作为策略
    BSWorkFlow::Instance()->reset();
    QList<int> ignoreRevenueList;
    QList<int> ignoreCostList;
    QList<int> ignoreProfitList;
    QList<BSEvent> eventList = BSEvent::randomEvent();
    QList<BSAction> ignoreActionList;
    for (int i = 0; i < eventList.size(); i++)
    {
        action = alg.ignoreSchedule(eventList[i]);
        if (ignoreProfitList.isEmpty())
        {
            ignoreCostList.append(action.cost);
            ignoreRevenueList.append(action.revenue);
            ignoreProfitList.append(action.profit);
        }
        else
        {
            ignoreCostList.append(ignoreCostList.last() + action.cost);
            ignoreRevenueList.append(ignoreRevenueList.last() + action.revenue);
            ignoreProfitList.append(ignoreProfitList.last() + action.profit);
        }
        alg.recovery(eventList[i], action);
        ignoreActionList.append(action);
    }

    qDebug() << "-------------------------------------------------------------------------------";
    qDebug() << "Use ignore action...";
    QString ignoreStrategyLog = QString("不作为策略(Ignore Strategy):\n");
    ignoreStrategyLog += QString("%1\n").arg(header);
    for (int i = 0; i < eventList.size(); i++)
    {
        ignoreStrategyLog += QString("%1\t%2\t%3\t")
                .arg(eventList[i].eventTime).arg(eventList[i].name()).arg(eventList[i].toString());
        ignoreStrategyLog += QString("%1\t%2\t")
                 .arg(ignoreActionList[i].name()).arg(ignoreActionList[i].toString());
        ignoreStrategyLog += QString("%1\t%2\t%3\n")
                 .arg(ignoreRevenueList[i]).arg(ignoreCostList[i]).arg(ignoreProfitList[i]);
    }
    currLog.append(ignoreStrategyLog);
    qDebug() << ignoreStrategyLog;
    qDebug() << "-------------------------------------------------------------------------------";
    // [1] End

    // [2] 随机策略
    BSWorkFlow::Instance()->reset();
    QList<int> randomRevenueList;
    QList<int> randomCostList;
    QList<int> randomProfitList;
    QList<BSAction> randomActionList;
    for (int i = 0; i < eventList.size(); i++)
    {
        action = alg.randomSchedule(eventList[i]);
        if (randomProfitList.isEmpty())
        {
            randomCostList.append(action.cost);
            randomRevenueList.append(action.revenue);
            randomProfitList.append(action.profit);
        }
        else
        {
            randomCostList.append(randomCostList.last() + action.cost);
            randomRevenueList.append(randomRevenueList.last() + action.revenue);
            randomProfitList.append(randomProfitList.last() + action.profit);
        }
        alg.recovery(eventList[i], action);
        randomActionList.append(action);
    }
    qDebug() << "-------------------------------------------------------------------------------";
    qDebug() << "Use random action...";
//    qDebug() << "Time" << "EventType" << "EventDetail" << "ActionType" << "ActionDetail"
//             << "Revenue" << "Cost" << "Profit";
//    for (int i = 0; i < randomProfitList.size(); i++)
//    {
//        qDebug() << eventList[i].eventTime << eventList[i].name() << eventList[i].toString()
//                 << randomActionList[i].name() << randomActionList[i].toString()
//                 << randomRevenueList[i] << randomCostList[i] << randomProfitList[i];
//    }
    QString randomStrategyLog = QString("随机策略(Random Strategy):\n");
    randomStrategyLog += QString("%1\n").arg(header);
    for (int i = 0; i < eventList.size(); i++)
    {
        randomStrategyLog += QString("%1\t%2\t%3\t")
                .arg(eventList[i].eventTime).arg(eventList[i].name()).arg(eventList[i].toString());
        randomStrategyLog += QString("%1\t%2\t")
                .arg(randomActionList[i].name()).arg(randomActionList[i].toString());
        randomStrategyLog += QString("%1\t%2\t%3\n")
                .arg(randomRevenueList[i]).arg(randomCostList[i]).arg(randomProfitList[i]);
    }
    currLog.append(randomStrategyLog);
    qDebug() << randomStrategyLog;
    qDebug() << "-------------------------------------------------------------------------------";
    // [2] End
    // [3] 最小成本策略
    BSWorkFlow::Instance()->reset();
    QList<int> minCostRevenueList;
    QList<int> minCostCostList;
    QList<int> minCostProfitList;
    QList<BSAction> minCostActionList;
    for (int i = 0; i < eventList.size(); i++)
    {
        action = alg.minCostSchedule(eventList[i]);
        if (minCostProfitList.isEmpty())
        {
            minCostCostList.append(action.cost);
            minCostRevenueList.append(action.revenue);
            minCostProfitList.append(action.profit);
        }
        else
        {
            minCostCostList.append(minCostCostList.last() + action.cost);
            minCostRevenueList.append(minCostRevenueList.last() + action.revenue);
            minCostProfitList.append(minCostProfitList.last() + action.profit);
        }
        alg.recovery(eventList[i], action);
        minCostActionList.append(action);
    }

    qDebug() << "-------------------------------------------------------------------------------";
    qDebug() << "Use minCcost action...";
//    qDebug() << "Time" << "EventType" << "EventDetail" << "ActionType" << "ActionDetail"
//             << "Revenue" << "Cost" << "Profit";
//    for (int i = 0; i < minCostProfitList.size(); i++)
//    {
//        qDebug() << eventList[i].eventTime << eventList[i].name() << eventList[i].toString()
//                 << minCostActionList[i].name() << minCostActionList[i].toString()
//                 << minCostRevenueList[i] << minCostCostList[i] << minCostProfitList[i];
//    }

    QString minCostStrategyLog = QString("最小成本策略(MinCost Strategy):\n");
    minCostStrategyLog += QString("%1\n").arg(header);
    for (int i = 0; i < eventList.size(); i++)
    {
        minCostStrategyLog += QString("%1\t%2\t%3\t")
                .arg(eventList[i].eventTime).arg(eventList[i].name()).arg(eventList[i].toString());
        minCostStrategyLog += QString("%1\t%2\t")
                .arg(minCostActionList[i].name()).arg(minCostActionList[i].toString());
        minCostStrategyLog += QString("%1\t%2\t%3\n")
                .arg(minCostRevenueList[i]).arg(minCostCostList[i]).arg(minCostProfitList[i]);
    }
    currLog.append(minCostStrategyLog);
    qDebug() << minCostStrategyLog;
    qDebug() << "-------------------------------------------------------------------------------";
    // [3] End
    // [4] 最大利润策略
    BSWorkFlow::Instance()->reset();
    QList<int> maxProfitRevenueList;
    QList<int> maxProfitCostList;
    QList<int> maxProfitProfitList;
    QList<BSAction> maxProfitActionList;
    for (int i = 0; i < eventList.size(); i++)
    {
        action = alg.maxProfitSchedule(eventList[i]);
        if (maxProfitProfitList.isEmpty())
        {
            maxProfitCostList.append(action.cost);
            maxProfitRevenueList.append(action.revenue);
            maxProfitProfitList.append(action.profit);
        }
        else
        {
            maxProfitCostList.append(maxProfitCostList.last() + action.cost);
            maxProfitRevenueList.append(maxProfitRevenueList.last() + action.revenue);
            maxProfitProfitList.append(maxProfitProfitList.last() + action.profit);
        }

        alg.recovery(eventList[i], action);
        maxProfitActionList.append(action);
    }

    qDebug() << "-------------------------------------------------------------------------------";
    qDebug() << "Use maxProfit action...";
//    qDebug() << "Time" << "EventType" << "EventDetail" << "ActionType" << "ActionDetail"
//             << "Revenue" << "Cost" << "Profit";
//    for (int i = 0; i < maxProfitProfitList.size(); i++)
//    {
//        qDebug() << eventList[i].eventTime << eventList[i].name() << eventList[i].toString()
//                 << maxProfitActionList[i].name() << maxProfitActionList[i].toString()
//                 << maxProfitRevenueList[i] << maxProfitCostList[i] << maxProfitProfitList[i];
//    }
    QString maxProfitStrategyLog = QString("最大利润策略(MaxProfit Strategy):\n");
    maxProfitStrategyLog += QString("%1\n").arg(header);
    for (int i = 0; i < eventList.size(); i++)
    {
        maxProfitStrategyLog += QString("%1\t%2\t%3\t")
                .arg(eventList[i].eventTime).arg(eventList[i].name()).arg(eventList[i].toString());
        maxProfitStrategyLog += QString("%1\t%2\t")
                .arg(maxProfitActionList[i].name()).arg(maxProfitActionList[i].toString());
        maxProfitStrategyLog += QString("%1\t%2\t%3\n")
                .arg(maxProfitRevenueList[i]).arg(maxProfitCostList[i]).arg(maxProfitProfitList[i]);
    }
    currLog.append(maxProfitStrategyLog);
    qDebug() << maxProfitStrategyLog;
    qDebug() << "-------------------------------------------------------------------------------";
    // [4] End

    /*
     * 开始Matlab画图
    **/
    const int BUFSIZE = 1024;
    char buffer[BUFSIZE] = {'\0'};
    engOutputBuffer(ep, buffer, BUFSIZE);

    // Make matlab code
    QString tString("t = [");
    QString revenueIgnoreString("revenueIgnore = [");
    QString revenueRandomString("revenueRandom = [");
    QString revenueMinCostString("revenueMinCost = [");
    QString revenueMaxProfitString("revenueMaxProfit = [");
    QString costIgnoreString("costIgnore = [");
    QString costRandomString("costRandom = [");
    QString costMinCostString("costMinCost = [");
    QString costMaxProfitString("costMaxProfit = [");
    QString profitIgnoreString("profitIgnore = [");
    QString profitRandomString("profitRandom = [");
    QString profitMinCostString("profitMinCost = [");
    QString profitMaxProfitString("profitMaxProfit = [");
    for (int i = 0; i < eventList.size(); i++)
    {
        tString += QString("%1 ").arg(eventList[i].eventTime);
        revenueIgnoreString += QString("%1 ").arg(ignoreRevenueList[i]);
        revenueRandomString += QString("%1 ").arg(randomRevenueList[i]);
        revenueMinCostString += QString("%1 ").arg(minCostRevenueList[i]);
        revenueMaxProfitString += QString("%1 ").arg(maxProfitRevenueList[i]);
        costIgnoreString += QString("%1 ").arg(ignoreCostList[i]);
        costRandomString += QString("%1 ").arg(randomCostList[i]);
        costMinCostString += QString("%1 ").arg(minCostCostList[i]);
        costMaxProfitString += QString("%1 ").arg(maxProfitCostList[i]);
        profitIgnoreString += QString("%1 ").arg(ignoreProfitList[i]);
        profitRandomString += QString("%1 ").arg(randomProfitList[i]);
        profitMinCostString += QString("%1 ").arg(minCostProfitList[i]);
        profitMaxProfitString += QString("%1 ").arg(maxProfitProfitList[i]);
    }
    tString = tString.trimmed() + "]; ";
    revenueIgnoreString = revenueIgnoreString.trimmed() + "]; ";
    revenueRandomString = revenueRandomString.trimmed() + "]; ";
    revenueMinCostString = revenueMinCostString.trimmed() + "]; ";
    revenueMaxProfitString = revenueMaxProfitString.trimmed() + "]; ";
    costIgnoreString = costIgnoreString.trimmed() + "]; ";
    costRandomString = costRandomString.trimmed() + "]; ";
    costMinCostString = costMinCostString.trimmed() + "]; ";
    costMaxProfitString = costMaxProfitString.trimmed() + "]; ";
    profitIgnoreString = profitIgnoreString.trimmed() + "]; ";
    profitRandomString = profitRandomString.trimmed() + "]; ";
    profitMinCostString = profitMinCostString.trimmed() + "]; ";
    profitMaxProfitString = profitMaxProfitString.trimmed() + "]; ";

    QString matlabCmd1("clear all; cd E:\\Dev\\MATLAB7\\work\\business_uc; ");
    QString matlabCmd2("test2( t,revenueIgnore,revenueRandom,revenueMinCost,revenueMaxProfit,costIgnore,costRandom,costMinCost,costMaxProfit,profitIgnore,profitRandom,profitMinCost,profitMaxProfit );");
    QString matlabCode = matlabCmd1
                 + tString
                 + revenueIgnoreString
                 + revenueRandomString
                 + revenueMinCostString
                 + revenueMaxProfitString
                 + costIgnoreString
                 + costRandomString
                 + costMinCostString
                 + costMaxProfitString
                 + profitIgnoreString
                 + profitRandomString
                 + profitMinCostString
                 + profitMaxProfitString
                 + matlabCmd2;

    qDebug() << "Matlab code: " << matlabCode;
    this->cmd = matlabCode;
    engEvalString(ep, matlabCode.toStdString().c_str());

    qDebug() << "BSTest::runTest2() Finished." << __FILE__ << __LINE__;
    qDebug() << "====================================================================";
}

void BSTest::runTest3()
{
    qDebug() << "BSTest::runTest3() ..." << __FILE__ << __LINE__;

    BSAlgorithm alg;
    BSEvent event;
    BSAction action;
    QList<BSAction> allAction;

    // Figure 1 - subplot 1
    event.eventType = BSEvent::REQUIREMENT_ADD_E2;
    event.eventTime = 1;
    event.e2Info.instanceID = 2;
    event.e2Info.reqVLevel = 1; // Mark
    event.e2Info.extraWTP = 2000; // Mark

    int xSize = 10;
    BSConfig::Instance()->reset();
    const int unitRPrice = BSConfig::Instance()->getUnitRPrice();
    const int unitRCancelCost = BSConfig::Instance()->getUnitRCancelCost();
    QList<double> unitRCancelCost_unitRPrice;
    QList<int> actionNameList;
    QList<int> actionProfitList;
    QList<int> ignoreProfitList;
    QList<int> resourceAddProfitList;
    QList<int> resourceTransProfitList;
    QList<int> forkNextProfitList;
    for (int i = 0; i <= 1.5 * xSize; i++)
    {
        double k = (double) i / xSize;
        int unitRCancelCost = unitRPrice * k;
        unitRCancelCost_unitRPrice.append(k);

        BSConfig::Instance()->setUnitRCancelCost(unitRCancelCost);
        allAction = alg.scheduleActionsWithIntMax(event);
        action = alg.schedule(event, false);

        if (action.aType == BSAction::IGNORE)
        {
            actionNameList.append(1);
        }
        else if (action.aType == BSAction::RESOURCE_ADD_PLAN)
        {
            actionNameList.append(2);
        }
        else if (action.aType == BSAction::RESOURCE_TRANS_PLAN)
        {
            actionNameList.append(3);
        }
        else if (action.aType == BSAction::FORK_NEXT_PERIOD)
        {
            actionNameList.append(4);
        }
        actionProfitList.append(action.profit);

        if (allAction.size() == 4)
        {
            for (int i = 0; i < allAction.size(); i++)
            {
                if (allAction[i].aType == BSAction::IGNORE)
                {
                    ignoreProfitList.append(allAction[i].profit);
                }
                else if (allAction[i].aType == BSAction::RESOURCE_ADD_PLAN)
                {
                    resourceAddProfitList.append(allAction[i].profit);
                }
                else if (allAction[i].aType == BSAction::RESOURCE_TRANS_PLAN)
                {
                    resourceTransProfitList.append(allAction[i].profit);
                }
                else if (allAction[i].aType == BSAction::FORK_NEXT_PERIOD)
                {
                    forkNextProfitList.append(allAction[i].profit);
                }
            }
        }
    }
    QString _x = "x = [";
    QString _actions = "actions = [";
    QString _profit = "profit = [";
    QString _ignore = "ignore = [";
    QString _resAdd = "resAdd = [";
    QString _resTrans = "resTrans = [";
    QString _forkNext = "forkNext = [";
    for (int i = 0; i < unitRCancelCost_unitRPrice.size(); i++)
    {
        _x += QString("%1 ").arg(unitRCancelCost_unitRPrice[i]);
        _actions += QString("%1 ").arg(actionNameList[i]);
        _profit += QString("%1 ").arg(actionProfitList[i]);
        _ignore += QString("%1 ").arg(ignoreProfitList[i]);
        _resAdd += QString("%1 ").arg(resourceAddProfitList[i]);
        _resTrans += QString("%1 ").arg(resourceTransProfitList[i]);
        _forkNext += QString("%1 ").arg(forkNextProfitList[i]);
    }
    _x = _x.trimmed().append("];");
    _actions = _actions.trimmed().append("];");
    _profit = _profit.trimmed().append("];");
    _ignore = _ignore.trimmed().append("];");
    _resAdd = _resAdd.trimmed().append("];");
    _resTrans = _resTrans.trimmed().append("];");
    _forkNext = _forkNext.trimmed().append("];");

    // Figure 1 - subplot 2
    event.eventType = BSEvent::REQUIREMENT_ADD_E2;
    event.eventTime = 1;
    event.e2Info.instanceID = 2;
    event.e2Info.reqVLevel = 1; // Mark
    QList<double> wtpXList;
    QList<int> wtpProfitList;
    QList<int> wtpActionNameList;
    BSConfig::Instance()->reset();
    for (int i = 0; i <= 1.5 * xSize; i++)
    {
        double k = (double) i / xSize;
        event.e2Info.extraWTP = k * unitRCancelCost; // Mark
        allAction = alg.scheduleActionsWithIntMax(event);
        action = alg.schedule(event, false);
        wtpXList.append(k);
        if (action.aType == BSAction::IGNORE)
        {
            wtpActionNameList.append(1);
        }
        else if (action.aType == BSAction::RESOURCE_ADD_PLAN)
        {
            wtpActionNameList.append(2);
        }
        else if (action.aType == BSAction::RESOURCE_TRANS_PLAN)
        {
            wtpActionNameList.append(3);
        }
        else if (action.aType == BSAction::FORK_NEXT_PERIOD)
        {
            wtpActionNameList.append(4);
        }
        wtpProfitList.append(action.profit);
    }
    QString _wtpX = "wtpX = [";
    QString _wtpActions = "wtpActions = [";
    QString _wtpProfit = "wtpProfit = [";
    assert(wtpXList.size() == wtpActionNameList.size() && wtpXList.size() == wtpProfitList.size());
    for (int i = 0; i < wtpXList.size(); i++)
    {
        _wtpX += QString("%1 ").arg(wtpXList[i]);
        _wtpActions += QString("%1 ").arg(wtpActionNameList[i]);
        _wtpProfit += QString("%1 ").arg(wtpProfitList[i]);
    }
    _wtpX = _wtpX.trimmed().append("];");
    _wtpActions = _wtpActions.trimmed().append("];");
    _wtpProfit = _wtpProfit.trimmed().append("];");
//    qDebug() << "wtpActionNameList=" << wtpActionNameList;

    // Figure 2 - subplot 1
    event.eventType = BSEvent::SERVICE_EXEC_DELAY_E5;
    event.eventTime = 10;
    event.e5Info.instanceID = 1;
    event.e5Info.sNodeID = 1;
    event.e5Info.timeDelay = 10; //Mark
    QList<double> delayXList;
    QList<int> delayProfitList;
    QList<int> delayActionNameList;
    BSConfig::Instance()->reset();
    const int unitDelayCost = BSConfig::Instance()->getUnitDelayCost();
    for (int i = 0; i <= xSize; i++)
    {
        double k = (double) i / xSize;
        int unitTimeDelayCost = unitDelayCost * k;
        BSConfig::Instance()->setUnitTimeDelayCost(unitTimeDelayCost);
        action = alg.schedule(event, false);
        delayXList.append(k);
        if (action.aType == BSAction::IGNORE)
        {
            delayActionNameList.append(1);
        }
        else if (action.aType == BSAction::CANCEL_INSTANCE)
        {
            delayActionNameList.append(2);
        }
        else if (action.aType == BSAction::DELAY_TO_NEXT_PEROID)
        {
            delayActionNameList.append(3);
        }
        delayProfitList.append(action.profit);
    }
    qDebug() << "delayActionNameList =" << delayActionNameList;
    QString _delayX = "delayX = [";
    QString _delayActions = "delayActions = [";
    QString _delayProfit = "delayProfit = [";
    assert(delayXList.size() == delayActionNameList.size() && delayXList.size() == delayProfitList.size());
    for (int i = 0; i < delayXList.size(); i++)
    {
        _delayX += QString("%1 ").arg(delayXList[i]);
        _delayActions += QString("%1 ").arg(delayActionNameList[i]);
        _delayProfit += QString("%1 ").arg(delayProfitList[i]);
    }
    _delayX = _delayX.trimmed().append("];");
    _delayActions = _delayActions.trimmed().append("];");
    _delayProfit = _delayProfit.trimmed().append("];");

    // Figure 2 - subplot 2
    event.eventType = BSEvent::SERVICE_EXEC_DELAY_E5;
    event.eventTime = 10;
    event.e5Info.instanceID = 1;
    event.e5Info.sNodeID = 1;
    event.e5Info.timeDelay = 10; //Mark
    BSConfig::Instance()->reset();
    const int unitTimeDelayCost = unitDelayCost * 0.3;
    QList<double> kList;
    QList<int> kActionList;
    QList<int> kProfitList;
    for (int i = 0; i <= 3 * xSize; i++)
    {
        double k = (double) i / xSize;
        BSConfig::Instance()->setUnitDelayCost((double) unitDelayCost * k);
        BSConfig::Instance()->setUnitTimeDelayCost((double) unitTimeDelayCost * k);
        action = alg.schedule(event, false);
        kList.append(k);
        if (action.aType == BSAction::IGNORE)
        {
            kActionList.append(1);
        }
        else if (action.aType == BSAction::CANCEL_INSTANCE)
        {
            kActionList.append(2);
        }
        else if (action.aType == BSAction::DELAY_TO_NEXT_PEROID)
        {
            kActionList.append(3);
        }
        kProfitList.append(action.profit);
    }
    QString _kX = "kX = [";
    QString _kActions = "kActions = [";
    QString _kProfits = "kProfits = [";
    assert(kList.size() == kActionList.size());
    for (int i = 0; i < kList.size(); i++)
    {
        _kX += QString("%1 ").arg(kList[i]);
        _kActions += QString("%1 ").arg(kActionList[i]);
        _kProfits += QString("%1 ").arg(kProfitList[i]);
    }
    _kX = _kX.trimmed().append("];");
    _kActions = _kActions.trimmed().append("];");
    _kProfits = _kProfits.trimmed().append("];");

    QString matlabCmd("clear all; cd E:\\Dev\\MATLAB7\\work\\business_uc;");
    matlabCmd += QString("%1 %2 %3 ").arg(_x).arg(_actions).arg(_profit);
    matlabCmd += QString("%1 %2 %3 ").arg(_wtpX).arg(_wtpActions).arg(_wtpProfit);
    matlabCmd += QString("%1 %2 %3 ").arg(_delayX).arg(_delayActions).arg(_delayProfit);
    matlabCmd += QString("%1 %2 %3 ").arg(_kX).arg(_kActions).arg(_kProfits);

//    matlabCmd += QString("%1 %2 %3 %4 %5 %6 %7  %8 %9 %10  %11 %12 %13").arg(_x).arg(_actions)
//            .arg(_profit).arg(_ignore).arg(_resAdd).arg(_resTrans).arg(_forkNext) // Test1
//            .arg(_wtpX).arg(_wtpActions).arg(_wtpProfit)
//            .arg(_delayX).arg(_delayActions).arg(_delayProfit);
//    matlabCmd.append(" test3_1(x, actions, profit, ignore, resAdd, resTrans, forkNext);");

    matlabCmd.append(" test3(x, actions, profit, wtpX, wtpActions, wtpProfit, delayX, delayActions, delayProfit, kX, kActions, kProfits);");

    engEvalString(ep, matlabCmd.toStdString().c_str());
    qDebug() << "Matlab CMD:" << matlabCmd;
    this->cmd = matlabCmd;
    qDebug() << "BSTest::runTest3() finished." << __FILE__ << __LINE__;
}

void BSTest::saveMatlabCmd()
{
    QString dateTime = QDateTime::currentDateTime().toString("yyyy.MM.dd hh:mm:ss");
    QFile outFile("matlab.log");
    outFile.open(QIODevice::WriteOnly | QIODevice::Append);
    QTextStream ts(&outFile);
    QString str("======================================================================\n");
    str += QString("DateTime: %1\nMatlabCmd:\n%2\nLog:\n%3\n")
            .arg(dateTime).arg(cmd).arg(currLog);
    str += QString("======================================================================");
    ts << str << endl;
    outFile.close();
}
