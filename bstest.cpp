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
    {   // ����Matlab����ָ�룬�������棻ʧ���򷵻�NULL
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
    BSWorkFlow::Instance()->reset();

    /* Test E1 �˿�����ȡ��/����
     * 1. ȡ�����������ڳ�������Դ����fork��һ��ʵ��
     *    �����¼���ʱ����ͬ��ʱ��֮��ֻ�ܲ���Ϊ
     */
    qDebug() << "====================================================================";
    qDebug() << "Test E1.1: ȡ�����������ڳ�������Դ����fork��һ��ʵ��,�����¼���ʱ����ͬ��ʱ��֮��ֻ�ܲ���Ϊ...";
    event.eventType = BSEvent::REQUIREMENT_CANCEL_REDUCE_E1;
    event.eventTime = 11; //Mark
    event.e1Info.instanceID = 1;
    event.e1Info.reqVLevel = 1;
    action = alg.schedule(event, true);
    qDebug() << "Test E1.1 result:";
    qDebug() << "EventType" << "EventDetail" << "ActionType" << "ActionDetail";
    qDebug() << event.name() << event.toString() << action.name() << action.toString();
    qDebug() << "--------------------------------------------------------------------";

    /* Test E1 �˿�����ȡ��/����
     * 2. ȡ�����������ڳ�������Դ��fork��һ��ʵ��,����ȡ����ʱ����ͬ��ʱ��֮ǰ
     */
    qDebug() << "Test E1.2: ȡ�����������ڳ�������Դ��fork��һ��ʵ��,����ȡ����ʱ����ͬ��ʱ��֮ǰ...";
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

    /* Test E2 �˿���������
     * 1. ����Ҫ��������ԴǨ�ƹ�������ѡ��Դ���Ѿ��㹻ִ��������Դ������
     */
    qDebug() << "Test E2.1: ����Ҫ��������ԴǨ�ƹ�������ѡ��Դ���Ѿ��㹻ִ��������Դ������...";
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

    /* Test E2 �˿���������
     * 2. ��ǰ������Դ������������һ���ں�ѡ��Դ�㹻������fork��ʵ������һ����
     */
    qDebug() << "Test E2.2: ��ǰ������Դ������������һ���ں�ѡ��Դ�㹻������fork��ʵ������һ����...";
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

    /* Test E2 �˿���������
     * 3. ��ǰ������Դ��������һ������ԴҲ������ֻ�ܽ�����Դת��
     */
    qDebug() << "Test E2.3: ��ǰ������Դ��������һ������ԴҲ������ֻ�ܽ�����Դת��...";
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

    /* Test E3 �����˿�����
     * 1. ��������Դ�㹻�ڵ�ǰ����fork��ʵ�������㣬������ڵ�ǰ����
     */
    qDebug() << "Test E3.1: ��������Դ�㹻�ڵ�ǰ����fork��ʵ�������㣬������ڵ�ǰ����...";
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

    /* Test E3 �����˿�����
     * 2. ��������Դ�����������ڵ�ǰ�������㣬��ô���Ƴٵ���һ����fork
     *   ����extraWTPҪ�㹻�����򲻹��ӳ��⳥
     */
    qDebug() << "Test E3.2: ��������Դ�����������ڵ�ǰ�������㣬��ô���Ƴٵ���һ����fork.����extraWTPҪ�㹻�����򲻹��ӳ��⳥...";
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

    /* Test E3 �����˿�����
     * 3. �����ں���һ���ڵ���Դ��������ֻ�ܲ���Ϊ
     *   ���߸���extraWTP������ֻ���ڲ���Ϊ
     */
    qDebug() << "Test E3.3: �����ں���һ���ڵ���Դ��������ֻ�ܲ���Ϊ.���߸���extraWTP������ֻ���ڲ���Ϊ...";
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

    /* Test E4 ��Դ����
     * 1. ��һ���ڵ���Դ��Ǩ�Ƶ���һ���ڵģ�����ȡ�����ֵ�ǰ�ģ�Ǩ�Ƶ���һ����
     */
    qDebug() << "Test E4.1: ��һ���ڵ���Դ��Ǩ�Ƶ���һ���ڵģ�����ȡ�����ֵ�ǰ�ģ�Ǩ�Ƶ���һ����...";
    event.eventType = BSEvent::RESOURCE_REDUCE_E4;
    event.eventTime = 10;
    event.e4Info.resType = 2;
    event.e4Info.vQlevel = 56;
    action = alg.schedule(event, true);
    qDebug() << "Test E4.1 result:";
    qDebug() << "EventType" << "EventDetail" << "ActionType" << "ActionDetail";
    qDebug() << event.name() << event.toString() << action.name() << action.toString();
    qDebug() << "--------------------------------------------------------------------";

    /* Test E4 ��Դ����
     * 1. ��һ���ڵ���Դ����Ǩ�Ƶ���һ���ڵģ�ֻ��ȡ����ǰ��
     */
    qDebug() << "Test E4.2: ��һ���ڵ���Դ����Ǩ�Ƶ���һ���ڵģ�ֻ��ȡ����ǰ��...";
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

    /* Test E5 ִ����ʱ
     * 1. ��ʱ��Ӱ��ͬ����㣬����ִ�в���Ϊ
     */
    qDebug() << "Test E5.1: ��ʱ��Ӱ��ͬ����㣬����ִ�в���Ϊ...";
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

    /* Test E5 ִ����ʱ
     * 2. ��ʱӰ����ͬ����㣬���ܲ���Ϊ����Ҫ�Ƴٵ�ǰʵ��
     */
    qDebug() << "Test E5.2: ��ʱӰ����ͬ����㣬���ܲ���Ϊ����Ҫ�Ƴٵ�ǰʵ��...";
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

    /* Test E5 ִ����ʱ
     * 3. ��һ�����ڵ���Դ�����������ӳ٣�ֻ��ȡ��/���ߺ��ԣ����Ե�ǰ����ȡ�������Ĵ��۸���
     */
    qDebug() << "Test E5.3: ��һ�����ڵ���Դ�����������ӳ٣�ֻ��ȡ��/���ߺ��ԣ����Ե�ǰ����ȡ�������Ĵ��۸���...";
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

    /* Test E6 ִ��ʧ��
     * 1. �Ѿ�ִ�е�ͬ����㣬��������
     */
    qDebug() << "Test E6.1: �Ѿ�ִ�е�ͬ����㣬��������...";
    event.eventType = BSEvent::SERVICE_EXEC_FAILED_E6;
    event.eventTime = 10;
    event.e6Info.instanceID = 1;
    event.e6Info.sNodeID = 2;
    action = alg.schedule(event, true);
    qDebug() << "Test E6.1 result:";
    qDebug() << "EventType" << "EventDetail" << "ActionType" << "ActionDetail";
    qDebug() << event.name() << event.toString() << action.name() << action.toString();
    qDebug() << "--------------------------------------------------------------------";

    /* Test E6 ִ��ʧ��
     * 2. ��û��ִ�е�ͬ����㣬���߹��Ͻ�㻹����ͬ����㣬��������
     */
    qDebug() << "Test E6.2: ��û��ִ�е�ͬ����㣬���߹��Ͻ�㻹����ͬ����㣬��������...";
    event.eventType = BSEvent::SERVICE_EXEC_FAILED_E6;
    event.eventTime = 1;
    event.e6Info.instanceID = 1;
    event.e6Info.sNodeID = 1; //Mark
    action = alg.schedule(event, true);
    qDebug() << "Test E6.2 result:";
    qDebug() << "EventType" << "EventDetail" << "ActionType" << "ActionDetail";
    qDebug() << event.name() << event.toString() << action.name() << action.toString();
    qDebug() << "--------------------------------------------------------------------";
    qDebug() << "====================================================================";
}

void BSTest::runTest2()
{
    /*
     *   ��ʼ�㷨���棬α���
    **/
    BSAlgorithm alg;
    BSAction action;

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
    qDebug() << "Time" << "EventType" << "EventDetail" << "ActionType" << "ActionDetail"
             << "Revenue" << "Cost" << "Profit";
    for (int i = 0; i < eventList.size(); i++)
    {
        qDebug() << eventList[i].eventTime << eventList[i].name() << eventList[i].toString()
                 << ignoreActionList[i].name() << ignoreActionList[i].toString()
                 << ignoreRevenueList[i] << ignoreCostList[i] << ignoreProfitList[i];
    }
    qDebug() << "-------------------------------------------------------------------------------";

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
    qDebug() << "Time" << "EventType" << "EventDetail" << "ActionType" << "ActionDetail"
             << "Revenue" << "Cost" << "Profit";
    for (int i = 0; i < randomProfitList.size(); i++)
    {
        qDebug() << eventList[i].eventTime << eventList[i].name() << eventList[i].toString()
                 << randomActionList[i].name() << randomActionList[i].toString()
                 << randomRevenueList[i] << randomCostList[i] << randomProfitList[i];
    }
    qDebug() << "-------------------------------------------------------------------------------";

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
    qDebug() << "Time" << "EventType" << "EventDetail" << "ActionType" << "ActionDetail"
             << "Revenue" << "Cost" << "Profit";
    for (int i = 0; i < minCostProfitList.size(); i++)
    {
        qDebug() << eventList[i].eventTime << eventList[i].name() << eventList[i].toString()
                 << minCostActionList[i].name() << minCostActionList[i].toString()
                 << minCostRevenueList[i] << minCostCostList[i] << minCostProfitList[i];
    }
    qDebug() << "-------------------------------------------------------------------------------";


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
    qDebug() << "Time" << "EventType" << "EventDetail" << "ActionType" << "ActionDetail"
             << "Revenue" << "Cost" << "Profit";
    for (int i = 0; i < maxProfitProfitList.size(); i++)
    {
        qDebug() << eventList[i].eventTime << eventList[i].name() << eventList[i].toString()
                 << maxProfitActionList[i].name() << maxProfitActionList[i].toString()
                 << maxProfitRevenueList[i] << maxProfitCostList[i] << maxProfitProfitList[i];
    }
    qDebug() << "-------------------------------------------------------------------------------";

    /*
     * ��ʼMatlab��ͼ
    **/
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
//    engEvalString(ep, "t");
//    engEvalString(ep, "cd E:\\Dev\\MATLAB7\\work\\business_uc; test( t,revenueIgnore,revenueRandom,revenueMinCost,revenueMaxProfit);");
//    qDebug() << buffer;


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
