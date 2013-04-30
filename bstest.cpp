#include <QList>
#include <QString>
#include <QDebug>
#include <engine.h>

#include "bstest.h"
#include "bsworkflow.h"
#include "bsevent.h"
#include "bsaction.h"
#include "bsalgorithm.h"

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
    BSAlgorithm alg;
    BSEvent event;
    BSAction action;

//    /* Test E1 顾客需求取消/降低
//     * 1. 取消的需求所腾出来的资源不够fork另一个实例
//     *    或发生事件的时间在同步时间之后，只能不作为
//     */
//    qDebug() << "E1, ignore...";
//    event.eventType = BSEvent::REQUIREMENT_CANCEL_REDUCE_E1;
//    event.time = 11; //Mark
//    event.e1Info.instanceID = 1;
//    event.e1Info.reqVLevel = 1;
//    action = alg.schedule(event, true);
//    qDebug() << "The result is:";
//    qDebug() << event.toString();
//    qDebug() << action.toString() << "\n";

//    /* Test E1 顾客需求取消/降低
//     * 2. 取消的需求所腾出来的资源够fork另一个实例,并且取消的时间在同步时间之前
//     */
//    qDebug() << "E1, fork...";
//    event.eventType = BSEvent::REQUIREMENT_CANCEL_REDUCE_E1;
//    event.time = 1; //Mark
//    event.e1Info.instanceID = 0;
//    event.e1Info.reqVLevel = 3;
//    action = alg.schedule(event, true);
//    qDebug() << "The result is:";
//    qDebug() << event.toString();
//    qDebug() << action.toString() << "\n";


//    /* Test E2 顾客需求增加
//         * 1. 不需要从其他资源迁移过来，候选资源就已经足够执行增加资源分配了
//         */
//    qDebug() << "E2, resource add...";
//    event.eventType = BSEvent::REQUIREMENT_ADD_E2;
//    event.time = 1;
//    event.e2Info.instanceID = 2;
//    event.e2Info.reqVLevel = 1; // Mark
//    event.e2Info.extraWTP = 2000;
//    action = alg.schedule(event, true);
//    qDebug() << "The result is:";
//    qDebug() << event.toString();
//    qDebug() << action.toString() << "\n";

//    /* Test E2 顾客需求增加
//         * 2. 当前周期资源不够，但是下一周期候选资源足够，可以fork新实例到下一周期
//         */
//    qDebug() << "E2, fork to next...";
//    event.eventType = BSEvent::REQUIREMENT_ADD_E2;
//    event.time = 1;
//    event.e2Info.instanceID = 2;
//    event.e2Info.reqVLevel = 2; // Mark
//    event.e2Info.extraWTP = 2000;
//    action = alg.schedule(event, true);
//    qDebug() << "The result is:";
//    qDebug() << event.toString();
//    qDebug() << action.toString() << "\n";

//    /* Test E2 顾客需求增加
//         * 3. 当前周期资源不够，下一周期资源也不够，只能进行资源转移
//         */
//    qDebug() << "E2, resource trans...";
//    event.eventType = BSEvent::REQUIREMENT_ADD_E2;
//    event.time = 1;
//    event.e2Info.instanceID = 2;
//    event.e2Info.reqVLevel = 2; // Mark
//    event.e2Info.extraWTP = 2000;
//    BSWorkFlow::Instance()->setResourceQLevel(1, 1, 0);
//    action = alg.schedule(event, true);
//    qDebug() << "The result is:";
//    qDebug() << event.toString();
//    qDebug() << action.toString() << "\n";

//    /* Test E3 新增顾客需求
//         * 1. 本周期资源足够在当前周期fork新实例来满足，最好是在当前周期
//         */
//    event.eventType = BSEvent::REQUIREMENT_NEW_E3;
//    event.time = 1;
//    event.e3Info.instanceID = 2;
//    event.e3Info.requirement.setFree(false);
//    event.e3Info.requirement.customer = BSWorkFlow::Instance()->bsRequirementQueue.size();
//    event.e3Info.requirement.qLevel = 1; //Mark
//    event.e3Info.requirement.wtp = 1000;
//    action = alg.schedule(event, true);
//    qDebug() << "The result is:";
//    qDebug() << event.toString();
//    qDebug() << action.toString() << "\n";

//    /* Test E3 新增顾客需求
//         * 2. 本周期资源不够，不能在当前周期满足，那么就推迟到下一周期fork
//         *   并且extraWTP要足够，否则不够延迟赔偿
//         */
//    event.eventType = BSEvent::REQUIREMENT_NEW_E3;
//    event.time = 1;
//    event.e3Info.instanceID = 2;
//    event.e3Info.requirement.setFree(false);
//    event.e3Info.requirement.customer = BSWorkFlow::Instance()->bsRequirementQueue.size();
//    event.e3Info.requirement.qLevel = 2; //Mark
//    event.e3Info.requirement.wtp = 2000; //Mark
//    action = alg.schedule(event, true);
//    qDebug() << "The result is:";
//    qDebug() << event.toString();
//    qDebug() << action.toString() << "\n";

//    /* Test E3 新增顾客需求
//         * 3. 本周期和下一周期的资源都不够，只能不作为
//         *   或者给的extraWTP不够，只能在不作为
//         */
//    event.eventType = BSEvent::REQUIREMENT_NEW_E3;
//    event.time = 1;
//    event.e3Info.instanceID = 2;
//    event.e3Info.requirement.setFree(false);
//    event.e3Info.requirement.customer = BSWorkFlow::Instance()->bsRequirementQueue.size();
//    event.e3Info.requirement.qLevel = 3; //Mark
//    event.e3Info.requirement.wtp = 1000; //Mark
//    action = alg.schedule(event, true);
//    qDebug() << "The result is:";
//    qDebug() << event.toString();
//    qDebug() << action.toString() << "\n";

//    /* Test E4 资源减少
//         * 1. 下一周期的资源够迁移到下一周期的，可以取消部分当前的，迁移到下一周期
//         */
//    event.eventType = BSEvent::RESOURCE_REDUCE_E4;
//    event.eventTime = 10;
//    event.e4Info.resType = 2;
//    event.e4Info.vQlevel = 56;
//    action = alg.schedule(event, true);
//    qDebug() << "The result is:";
//    qDebug() << event.toString();
//    qDebug() << action.toString() << "\n";

//    /* Test E4 资源减少
//         * 1. 下一周期的资源不够迁移到下一周期的，只能取消当前的
//         */
//    event.eventType = BSEvent::RESOURCE_REDUCE_E4;
//    event.time = 10;
//    event.e4Info.resType = 2;
//    event.e4Info.vQlevel = 56;
//    BSWorkFlow::Instance()->setResourceQLevel(1, 2, 0);
//    action = alg.schedule(event, true);
//    qDebug() << "The result is:";
//    qDebug() << event.toString();
//    qDebug() << action.toString() << "\n";

//    /* Test E5 执行延时
//         * 1. 延时不影响同步结点，可以执行不作为
//         */
//    event.eventType = BSEvent::SERVICE_EXEC_DELAY_E5;
//    event.time = 10;
//    event.e5Info.instanceID = 1;
//    event.e5Info.sNodeID = 1;
//    event.e5Info.timeDelay = 1; //Mark
//    action = alg.schedule(event, true);
//    qDebug() << "The result is:";
//    qDebug() << event.toString();
//    qDebug() << action.toString() << "\n";

//    /* Test E5 执行延时
//         * 2. 延时影响了同步结点，不能不作为，需要推迟当前实例
//         */
//    event.eventType = BSEvent::SERVICE_EXEC_DELAY_E5;
//    event.time = 10;
//    event.e5Info.instanceID = 1;
//    event.e5Info.sNodeID = 1;
//    event.e5Info.timeDelay = 10; //Mark
//    action = alg.schedule(event, true);
//    qDebug() << "The result is:";
//    qDebug() << event.toString();
//    qDebug() << action.toString() << "\n";

//    /* Test E5 执行延时
//         * 3. 后一个周期的资源不够，不能延迟，只能取消/或者忽略，忽略的前提是取消带来的代价更大
//         */
//    event.eventType = BSEvent::SERVICE_EXEC_DELAY_E5;
//    event.time = 10;
//    event.e5Info.instanceID = 1;
//    event.e5Info.sNodeID = 1;
//    event.e5Info.timeDelay = 10; //Mark
//    BSWorkFlow::Instance()->setResourceQLevel(1, 2, 0);
//    action = alg.schedule(event, true);
//    qDebug() << "The result is:";
//    qDebug() << event.toString();
//    qDebug() << action.toString() << "\n";

//    /* Test E6 执行失败
//         * 1. 已经执行到同步结点，不能重试
//         */
//    event.eventType = BSEvent::SERVICE_EXEC_FAILED_E6;
//    event.time = 10;
//    event.e6Info.instanceID = 1;
//    event.e6Info.sNodeID = 2;
//    action = alg.schedule(event, true);
//    qDebug() << "The result is:";
//    qDebug() << event.toString();
//    qDebug() << action.toString() << "\n";

//    /* Test E6 执行失败
//         * 2. 还没有执行到同步结点，或者故障结点还不是同步结点，可以重试
//         */
//    event.eventType = BSEvent::SERVICE_EXEC_FAILED_E6;
//    event.time = 1;
//    event.e6Info.instanceID = 1;
//    event.e6Info.sNodeID = 1; //Mark
//    action = alg.schedule(event, true);
//    qDebug() << "The result is:";
//    qDebug() << event.toString();
//    qDebug() << action.toString() << "\n";
}

void BSTest::runTest2()
{
    BSAlgorithm alg;
    BSAction action;

    QList<int> ignoreRevenueList;
    QList<int> ignoreCostList;
    QList<int> ignoreProfitList;
    QList<BSEvent> eventList = BSEvent::randomEvent();
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
//        qDebug() << eventList[i].toString()
//            << action.toString()
//            << maxProfitProfitList[i];
    }

    qDebug() << "---------------All Ignore-----------------------------";
    qDebug() << "Revenue" << "Cost" << "Profit";
    for (int i = 0; i < ignoreProfitList.size(); i++)
    {
        qDebug() << ignoreRevenueList[i] << ignoreCostList[i] << ignoreProfitList[i];
    }

    BSWorkFlow::Instance()->reset();
    QList<int> randomRevenueList;
    QList<int> randomCostList;
    QList<int> randomProfitList;
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
//        qDebug() << eventList[i].toString()
//            << action.toString()
//            << randomProfitList[i];
    }
    qDebug() << "---------------Random-----------------------------";
    qDebug() << "Revenue" << "Cost" << "Profit";
    for (int i = 0; i < randomProfitList.size(); i++)
    {
        qDebug() << randomRevenueList[i] << randomCostList[i] << randomProfitList[i];
    }

    BSWorkFlow::Instance()->reset();
    QList<int> minCostRevenueList;
    QList<int> minCostCostList;
    QList<int> minCostProfitList;
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
//        qDebug() << eventList[i].toString()
//            << action.toString()
//            << minCostProfitList[i];
    }

    qDebug() << "---------------MinCost-----------------------------";
    qDebug() << "Revenue" << "Cost" << "Profit";
    for (int i = 0; i < minCostProfitList.size(); i++)
    {
        qDebug() << minCostRevenueList[i] << minCostCostList[i] << minCostProfitList[i];
    }


    BSWorkFlow::Instance()->reset();
    QList<int> maxProfitRevenueList;
    QList<int> maxProfitCostList;
    QList<int> maxProfitProfitList;
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
//        qDebug() << eventList[i].toString()
//            << action.toString()
//            << maxProfitProfitList[i];
    }

    qDebug() << "---------------MaxProfit-----------------------------";
    qDebug() << "Revenue" << "Cost" << "Profit";
    for (int i = 0; i < maxProfitProfitList.size(); i++)
    {
        qDebug() << maxProfitRevenueList[i] << maxProfitCostList[i] << maxProfitProfitList[i];
    }


    // Begin plot


    const int BUFSIZE = 1024;
    char buffer[BUFSIZE] = {'\0'};
    engOutputBuffer(ep, buffer, BUFSIZE);

    double *t = new double[eventList.size()];

    double *revenueIgnore = new double[eventList.size()];
    double *revenueRandom = new double[eventList.size()];
    double *revenueMinCost = new double[eventList.size()];
    double *revenueMaxProfit = new double[eventList.size()];

    double *costIgnore = new double[eventList.size()];
    double *costRandom = new double[eventList.size()];
    double *costMinCost = new double[eventList.size()];
    double *costMaxProfit = new double[eventList.size()];

    double *profitIgnore = new double[eventList.size()];
    double *profitRandom = new double[eventList.size()];
    double *profitMinCost = new double[eventList.size()];
    double *profitMaxProfit = new double[eventList.size()];

    for (int i = 0; i < eventList.size(); i++)
    {
        t[i] = eventList[i].eventTime;

        revenueIgnore[i] = ignoreRevenueList[i];
        revenueRandom[i] = randomRevenueList[i];
        revenueMinCost[i] = minCostRevenueList[i];
        revenueMaxProfit[i] = maxProfitRevenueList[i];

        costIgnore[i] = ignoreCostList[i];
        costRandom[i] = randomCostList[i];
        costMinCost[i] = minCostCostList[i];
        costMaxProfit[i] = maxProfitCostList[i];

        profitIgnore[i] = ignoreProfitList[i];
        profitRandom[i] = randomProfitList[i];
        profitMinCost[i] = minCostProfitList[i];
        profitMaxProfit[i] = maxProfitProfitList[i];
    }

    engEvalString(ep, "clear;");

    mxArray *_t = mxCreateDoubleMatrix(1, eventList.size(), mxREAL);
    memcpy(mxGetPr(_t), t, eventList.size()*sizeof(double));
    engPutVariable(ep, "t", _t);

    mxArray *_revenueIgnore = mxCreateDoubleMatrix(1, eventList.size(), mxREAL);
    memcpy(mxGetPr(_revenueIgnore), revenueIgnore, eventList.size()*sizeof(double));
    engPutVariable(ep, "revenueIgnore", _revenueIgnore);

    mxArray *_revenueRandom = mxCreateDoubleMatrix(1, eventList.size(), mxREAL);
    memcpy(mxGetPr(_revenueRandom), revenueRandom, eventList.size()*sizeof(double));
    engPutVariable(ep, "revenueRandom", _revenueRandom);

    mxArray *_revenueMinCost = mxCreateDoubleMatrix(1, eventList.size(), mxREAL);
    memcpy(mxGetPr(_revenueMinCost), revenueMinCost, eventList.size()*sizeof(double));
    engPutVariable(ep, "revenueMinCost", _revenueMinCost);

    mxArray *_revenueMaxProfit = mxCreateDoubleMatrix(1, eventList.size(), mxREAL);
    memcpy(mxGetPr(_revenueMaxProfit), revenueMaxProfit, eventList.size()*sizeof(double));
    engPutVariable(ep, "revenueMaxProfit", _revenueMaxProfit);

    mxArray *_costIgnore = mxCreateDoubleMatrix(1, eventList.size(), mxREAL);
    memcpy(mxGetPr(_costIgnore), costIgnore, eventList.size()*sizeof(double));
    engPutVariable(ep, "costIgnore", _costIgnore);

    mxArray *_costRandom = mxCreateDoubleMatrix(1, eventList.size(), mxREAL);
    memcpy(mxGetPr(_costRandom), costRandom, eventList.size()*sizeof(double));
    engPutVariable(ep, "costRandom", _costRandom);

    mxArray *_costMinCost = mxCreateDoubleMatrix(1, eventList.size(), mxREAL);
    memcpy(mxGetPr(_costMinCost), costMinCost, eventList.size()*sizeof(double));
    engPutVariable(ep, "costMinCost", _costMinCost);

    mxArray *_costMaxProfit = mxCreateDoubleMatrix(1, eventList.size(), mxREAL);
    memcpy(mxGetPr(_costMaxProfit), costMaxProfit, eventList.size()*sizeof(double));
    engPutVariable(ep, "costMaxProfit", _costMaxProfit);

    mxArray *_profitIgnore = mxCreateDoubleMatrix(1, eventList.size(), mxREAL);
    memcpy(mxGetPr(_profitIgnore), profitIgnore, eventList.size()*sizeof(double));
    engPutVariable(ep, "profitIgnore", _profitIgnore);

    mxArray *_profitRandom = mxCreateDoubleMatrix(1, eventList.size(), mxREAL);
    memcpy(mxGetPr(_profitRandom), profitRandom, eventList.size()*sizeof(double));
    engPutVariable(ep, "profitRandom", _profitRandom);

    mxArray *_profitMinCost = mxCreateDoubleMatrix(1, eventList.size(), mxREAL);
    memcpy(mxGetPr(_profitMinCost), profitMinCost, eventList.size()*sizeof(double));
    engPutVariable(ep, "profitMinCost", _profitMinCost);

    mxArray *_profitMaxProfit = mxCreateDoubleMatrix(1, eventList.size(), mxREAL);
    memcpy(mxGetPr(_profitMaxProfit), profitMaxProfit, eventList.size()*sizeof(double));
    engPutVariable(ep, "profitMaxProfit", _profitMaxProfit);

    engEvalString(ep, "cd E:\\Dev\\MATLAB7\\work\\business_uc; test2( t,revenueIgnore,revenueRandom,revenueMinCost,revenueMaxProfit,costIgnore,costRandom,costMinCost,costMaxProfit,profitIgnore,profitRandom,profitMinCost,profitMaxProfit );");
    qDebug() << buffer;


    mxDestroyArray(_t);
    mxDestroyArray(_revenueIgnore);
    mxDestroyArray(_revenueRandom);
    mxDestroyArray(_revenueMinCost);
    mxDestroyArray(_revenueMaxProfit);
    mxDestroyArray(_costIgnore);
    mxDestroyArray(_costRandom);
    mxDestroyArray(_costMinCost);
    mxDestroyArray(_costMaxProfit);
    mxDestroyArray(_profitIgnore);
    mxDestroyArray(_profitRandom);
    mxDestroyArray(_profitMinCost);
    mxDestroyArray(_profitMaxProfit);

    delete[] t;

    delete[] revenueIgnore;
    delete[] revenueRandom;
    delete[] revenueMinCost;
    delete[] revenueMaxProfit;

    delete[] costIgnore;
    delete[] costRandom;
    delete[] costMinCost;
    delete[] costMaxProfit;

    delete[] profitIgnore;
    delete[] profitRandom;
    delete[] profitMinCost;
    delete[] profitMaxProfit;


}
