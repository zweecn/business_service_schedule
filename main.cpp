#include <QtGui/QApplication>
#include <QDebug>
#include <QBitArray>
#include <climits>
#include <iostream>

#include "bsmainwidget.h"
#include "bsworkflow.h"
#include "singleton.h"
#include "bsconfig.h"
#include "bsevent.h"
#include "bsaction.h"
#include "bsalgorithm.h"
#include "bsinstance.h"
#include "bssnodeplan.h"

int main(int argc, char *argv[])
{
//    QApplication a(argc, argv);
//    BSMainWidget w;
//    w.show();
//    return a.exec();

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
//    event.e1Info.instanceID = 2;
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
//     * 1. 不需要从其他资源迁移过来，候选资源就已经足够执行增加资源分配了
//     */
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
//     * 2. 当前周期资源不够，但是下一周期候选资源足够，可以fork新实例到下一周期
//     */
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
//     * 3. 当前周期资源不够，下一周期资源也不够，只能进行资源转移
//     */
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
//     * 1. 本周期资源足够在当前周期fork新实例来满足，最好是在当前周期
//     */
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
//     * 2. 本周期资源不够，不能在当前周期满足，那么就推迟到下一周期fork
//     *   并且extraWTP要足够，否则不够延迟赔偿
//     */
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
//     * 3. 本周期和下一周期的资源都不够，只能不作为
//     *   或者给的extraWTP不够，只能在不作为
//     */
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

    /* Test E4 新增顾客需求
     * 3. 本周期和下一周期的资源都不够，只能不作为
     *   或者给的extraWTP不够，只能在不作为
     */
//    event.eventType = BSEvent::RESOURCE_REDUCE_E4;
//    event.time = 10;
//    event.e4Info.resType = 2;
//    event.e4Info.vQlevel = 56;

    // All is infruence
//    event.eventType = BSEvent::SERVICE_EXEC_DELAY_E5;
//    event.time = 10;
//    event.e5Info.instanceID = 1;
//    event.e5Info.sNodeID = 1;
//    event.e5Info.timeDelay = 10;

//    // Cur is infruence
//    event.eventType = BSEvent::SERVICE_EXEC_DELAY_E5;
//    event.time = 10;
//    event.e5Info.instanceID = 1;
//    event.e5Info.sNodeID = 1;
//    event.e5Info.timeDelay = 1;

// No NEED RETRY
//    event.eventType = BSEvent::SERVICE_EXEC_FAILED_E6;
//    event.time = 10;
//    event.e6Info.instanceID = 1;
//    event.e6Info.sNodeID = 2;
//    BSAction action = alg.schedule(event);

    // Need retry
//    event.eventType = BSEvent::SERVICE_EXEC_FAILED_E6;
//    event.time = 10;
//    event.e6Info.instanceID = 1;
//    event.e6Info.sNodeID = 1;

//    action = alg.schedule(event);

//    qDebug() << "\nThe result is:";
//    qDebug() << event.toString();
//    qDebug() << action.toString() << "\n";


    BSWorkFlow::Instance()->showSNodeList();
    BSWorkFlow::Instance()->showResourceList();
    BSWorkFlow::Instance()->showInstanceList();
    BSWorkFlow::Instance()->showRequirementQueue();

    return 0;
}
