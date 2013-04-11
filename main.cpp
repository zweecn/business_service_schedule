#include <QtGui/QApplication>
#include <QDebug>

#include "bsmainwidget.h"
#include "bsworkflow.h"
#include "singleton.h"
#include "bsconfig.h"
#include "bsevent.h"
#include "bsaction.h"
#include "bsalgorithm.h"

int main(int argc, char *argv[])
{
//    QApplication a(argc, argv);
//    BSMainWidget w;
//    w.show();
//    return a.exec();

//    BSWorkFlow::Instance()->showInstanceList();
//    BSWorkFlow::Instance()->showRequirementQueue();
//    BSWorkFlow::Instance()->showSNodeList();
//    BSWorkFlow::Instance()->showResourceList();

//    qDebug() << BSConfig::Instance()->getUnitCompensatePrice();
//    qDebug() << BSConfig::Instance()->getUnitDelayCost();
//    qDebug() << BSConfig::Instance()->getUnitRCancelCost();
//    qDebug() << BSConfig::Instance()->getUnitRPrice();
//    qDebug() << BSConfig::Instance()->getUnitTimeDelayCost();

    BSAlgorithm alg;
    BSEvent event;
    event.eventType = BSEvent::REQUIREMENT_CANCEL_E1;
    event.time = 1;
    event.e1Info.instanceID = 2;
    event.e1Info.reqVLevel = 2;
    BSAction action = alg.schedule(event);

    qDebug() << action.toString();

    return 0;
}
