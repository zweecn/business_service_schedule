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
    resize(400, 150);

    connect(this->saveWorkFlowInfoButton, SIGNAL(clicked()), this, SLOT(saveWorkFlow()));
    connect(this->test1Button, SIGNAL(clicked()), this, SLOT(matlabTest1()));
    connect(this->test2Button, SIGNAL(clicked()), this, SLOT(matlabTest2()));
}

void BSMainWidget::createButtons()
{
    logLabel = new QLabel(tr("日志文件: ./bs.log"));
    saveWorkFlowInfoButton = new QPushButton(tr("保存流程"));
    test1Button = new QPushButton(tr("实验1"));
    test2Button = new QPushButton(tr("实验2"));
    test3Button = new QPushButton(tr("实验3"));
    buttonGroup = new QGroupBox();
    QGridLayout *layout = new QGridLayout;
    layout->addWidget(logLabel, 0, 0, 1, 5);
    layout->addWidget(saveWorkFlowInfoButton, 1, 0);
    layout->setRowStretch(0, 1);
    layout->setColumnStretch(1, 1);
    layout->addWidget(test1Button, 1, 2);
    layout->addWidget(test2Button, 1, 3);
    layout->addWidget(test3Button, 1, 4);
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
    qDebug() << "DateTime:" << dateTime;
    logLabel->setText(QString("<p>DateTime: %1</p> <p>LogFile: ./bs.log</p>").arg(dateTime));
    test.runTest1();
    test1Button->setEnabled(true);
}

void BSMainWidget::matlabTest2()
{
    test2Button->setEnabled(false);
    QString dateTime = QDateTime::currentDateTime().toString("yyyy.MM.dd hh:mm:ss");
    qDebug() << "DateTime:" << dateTime;
    logLabel->setText(QString("<p>DateTime: %1</p> <p>LogFile: ./bs.log</p>").arg(dateTime));
    test.runTest2();
    test2Button->setEnabled(true);
}
