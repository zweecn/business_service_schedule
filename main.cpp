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

//    BSWorkFlow::Instance()->showSNodeList();
//    BSWorkFlow::Instance()->showResourceList();
//    BSWorkFlow::Instance()->showInstanceList();
//    BSWorkFlow::Instance()->showRequirementQueue();

    BSAlgorithm alg;
    BSEvent event;
//    event.eventType = BSEvent::REQUIREMENT_CANCEL_REDUCE_E1;
//    event.time = 11;
//    event.e1Info.instanceID = 2;
//    event.e1Info.reqVLevel = 1;
//    BSAction action = alg.schedule(event);

//    event.eventType = BSEvent::REQUIREMENT_ADD_E2;
//    event.time = 1;
//    event.e2Info.instanceID = 2;
//    event.e2Info.reqVLevel = 1; // OR 2, then find the diff
//    event.e2Info.extraWTP = 2000;

//    event.eventType = BSEvent::REQUIREMENT_NEW_E3;
//    event.time = 1;
//    event.e3Info.instanceID = 2;
//    event.e3Info.requirement.setFree(false);
//    event.e3Info.requirement.customer = BSWorkFlow::Instance()->bsRequirementQueue.size();
//    event.e3Info.requirement.qLevel = 1;
//    event.e3Info.requirement.wtp = 1000;

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
    event.eventType = BSEvent::SERVICE_EXEC_FAILED_E6;
    event.time = 10;
    event.e6Info.instanceID = 1;
    event.e6Info.sNodeID = 1;
    BSAction action = alg.schedule(event);

    qDebug() << "The result is: --------------------------------------------------------";
    qDebug() << event.toString();
    qDebug() << action.toString();


    return 0;
}
