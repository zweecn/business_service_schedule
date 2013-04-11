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

    BSAlgorithm alg;
    BSEvent event;
    event.eventType = BSEvent::REQUIREMENT_CANCEL_REDUCE_E1;
    event.time = 11;
    event.e1Info.instanceID = 2;
    event.e1Info.reqVLevel = 1;
    BSAction action = alg.schedule(event);

    qDebug() << event.toString();
    qDebug() << action.toString();

    return 0;
}
