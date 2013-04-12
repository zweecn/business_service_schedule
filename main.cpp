#include <QtGui/QApplication>
#include <QDebug>
#include <QBitArray>
#include <climits>

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

    event.eventType = BSEvent::REQUIREMENT_ADD_E2;
    event.time = 1;
    event.e2Info.instanceID = 2;
    event.e2Info.reqVLevel = 1;
    event.e2Info.extraWTP = 2000;
    BSAction action = alg.schedule(event);

//    qDebug() << event.toString();
//    qDebug() << action.toString();


    return 0;
}
