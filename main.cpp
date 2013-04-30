#include <QtGui/QApplication>
#include <QDebug>
#include <QBitArray>
#include <climits>
#include <iostream>
#include <cstdio>
#include <cmath>
#include <engine.h>

#include "bsmainwidget.h"
#include "bsworkflow.h"
#include "singleton.h"
#include "bsconfig.h"
#include "bsevent.h"
#include "bsaction.h"
#include "bsalgorithm.h"
#include "bsinstance.h"
#include "bssnodeplan.h"
#include "bstest.h"

int main(int argc, char *argv[])
{
    //    QApplication a(argc, argv);
    //    BSMainWidget w;
    //    w.show();
    //    return a.exec();



    BSTest t;
    t.runTest2();

//    BSWorkFlow::Instance()->showSNodeList();
//    BSWorkFlow::Instance()->showResourceList();
//    BSWorkFlow::Instance()->showInstanceList();
//    BSWorkFlow::Instance()->showRequirementQueue();

    return 0;
}
