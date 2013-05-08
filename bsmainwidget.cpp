#include <QDebug>
#include <QDateTime>

#include "bsmainwidget.h"
#include "bstest.h"
#include "bsworkflow.h"

BSMainWidget::BSMainWidget(QWidget *parent) :
    QWidget(parent)
{
    createButtons();

    QVBoxLayout *mainLayout = new QVBoxLayout;
//    mainLayout->addStretch();
    mainLayout->addWidget(buttonGroup);
    setLayout(mainLayout);

    setWindowTitle(tr("测试窗口"));
    resize(500, 150);

    connect(this->saveWorkFlowInfoButton, SIGNAL(clicked()), this, SLOT(saveWorkFlow()));
    connect(this->test1Button, SIGNAL(clicked()), this, SLOT(matlabTest1()));
    connect(this->test2Button, SIGNAL(clicked()), this, SLOT(matlabTest2()));
    connect(this->test3Button, SIGNAL(clicked()), this, SLOT(matlabTest3()));
    connect(this->saveMatlabCmdButton, SIGNAL(clicked()), this, SLOT(saveMatlabCmd()));
}

void BSMainWidget::createButtons()
{
    logLabel = new QLabel(tr("日志文件: ./bs.log"));
    saveWorkFlowInfoButton = new QPushButton(tr("保存流程"));
    test1Button = new QPushButton(tr("实验1"));
    test2Button = new QPushButton(tr("实验2"));
    test3Button = new QPushButton(tr("实验3"));
    saveMatlabCmdButton = new QPushButton(tr("保存Matlab语句"));
    buttonGroup = new QGroupBox();
    QGridLayout *layout = new QGridLayout;
    layout->addWidget(logLabel, 0, 0, 1, 6);
    layout->addWidget(saveWorkFlowInfoButton, 1, 0);
    layout->addWidget(saveMatlabCmdButton, 1, 1);
    layout->setRowStretch(0, 1);
    layout->setColumnStretch(2, 1);
    layout->addWidget(test1Button, 1, 3);
    layout->addWidget(test2Button, 1, 4);
    layout->addWidget(test3Button, 1, 5);
    buttonGroup->setLayout(layout);
}

void BSMainWidget::saveWorkFlow()
{
    BSWorkFlow::Instance()->reset();
    BSWorkFlow::Instance()->showWorkFlowInfo();
}

void BSMainWidget::matlabTest1()
{
    test1Button->setEnabled(false);
    QString dateTime = QDateTime::currentDateTime().toString("yyyy.MM.dd hh:mm:ss");
    qDebug() << "BSMainWidget::matlabTest1()..." << __FILE__ << __LINE__;
    qDebug() << "DateTime:" << dateTime;
    logLabel->setText(QString("<p>DateTime: %1</p> <p>LogFile: ./bs.log</p>").arg(dateTime));
    test.runTest1();
    test1Button->setEnabled(true);
    qDebug() << "BSMainWidget::matlabTest1() finished." << __FILE__ << __LINE__;
}

void BSMainWidget::matlabTest2()
{
    test2Button->setEnabled(false);
    QString dateTime = QDateTime::currentDateTime().toString("yyyy.MM.dd hh:mm:ss");
    qDebug() << "BSMainWidget::matlabTest2()..." << __FILE__ << __LINE__;
    qDebug() << "DateTime:" << dateTime;
    logLabel->setText(QString("<p>DateTime: %1</p> <p>LogFile: ./bs.log</p>").arg(dateTime));
    test.runTest2();
    test2Button->setEnabled(true);
    qDebug() << "BSMainWidget::matlabTest2() finished." << __FILE__ << __LINE__;
}

void BSMainWidget::matlabTest3()
{
    test2Button->setEnabled(false);
    QString dateTime = QDateTime::currentDateTime().toString("yyyy.MM.dd hh:mm:ss");
    qDebug() << "BSMainWidget::matlabTest3()..." << __FILE__ << __LINE__;
    qDebug() << "DateTime:" << dateTime;
    logLabel->setText(QString("<p>DateTime: %1</p> <p>LogFile: ./bs.log</p>").arg(dateTime));
    test.runTest3();
    test2Button->setEnabled(true);
    qDebug() << "BSMainWidget::matlabTest3() finished." << __FILE__ << __LINE__;
}

void BSMainWidget::saveMatlabCmd()
{
    qDebug() << "BSMainWidget::saveMatlabCmd()..." << __FILE__ << __LINE__;
    test.saveMatlabCmd();
    qDebug() << "BSMainWidget::saveMatlabCmd() finished." << __FILE__ << __LINE__;
}
