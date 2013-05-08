#include <QtGui/QApplication>
#include <QDebug>
#include <QBitArray>
#include <climits>
#include <iostream>
#include <cstdio>
#include <cmath>
#include <engine.h>
#include <QTextCodec>
#include <QFile>
#include <QTime>

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

void customMessageHandler(QtMsgType type, const char* msg)
{
    QString txt;
    switch(type)
    {
    case QtDebugMsg:
        txt = QString("Debug: %1").arg(msg);
        break;
    case QtWarningMsg:
        txt = QString("Warning: %1").arg(msg);
        break;
    case QtCriticalMsg:
        txt = QString("Critical: %1").arg(msg);
        break;
    case QtFatalMsg:
        txt = QString("Critical: %1").arg(msg);
        abort();
    }
    QFile outFile("bs.log");
    outFile.open(QIODevice::WriteOnly | QIODevice::Append);
    QTextStream ts(&outFile);
    ts << txt << endl;
}

void printExitInfo()
{
    qDebug() << "main() finished." << __FILE__ << __LINE__;
    QString dateTime = QDateTime::currentDateTime().toString("yyyy.MM.dd hh:mm:ss");
    qDebug() << "DateTime:" << dateTime;
    qDebug() << "##########################################################################";
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTextCodec *gbk = QTextCodec::codecForName("GBK");
    QTextCodec::setCodecForTr(gbk);
    QTextCodec::setCodecForCStrings(gbk);
    QTextCodec::setCodecForLocale(gbk);
    QTextCodec::setCodecForTr(gbk);
    QTextCodec::setCodecForLocale(gbk);
    QTextCodec::setCodecForCStrings(gbk);

    qInstallMsgHandler(customMessageHandler);

    qDebug() << "##########################################################################";
    qDebug() << "main()..." << __FILE__ << __LINE__;
    QString dateTime = QDateTime::currentDateTime().toString("yyyy.MM.dd hh:mm:ss");
    qDebug() << "DateTime:" << dateTime;

    BSMainWidget w;
    w.show();

    atexit(printExitInfo);
    return a.exec();
}
