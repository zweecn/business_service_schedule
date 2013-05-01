#ifndef BSMAINWIDGET_H
#define BSMAINWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QLayout>
#include <QGroupBox>
#include <QLabel>

#include "bstest.h"

class BSMainWidget : public QWidget
{
    Q_OBJECT
public:
    explicit BSMainWidget(QWidget *parent = 0);

signals:

public slots:
    void saveWorkFlow();
    void matlabTest1();
    void matlabTest2();

private:
    void createButtons();

    QGroupBox *buttonGroup;
    QPushButton *saveWorkFlowInfoButton;
    QPushButton *test1Button;
    QPushButton *test2Button;
    QPushButton *test3Button;
    QLabel* logLabel;

    BSTest test;
};

#endif // BSMAINWIDGET_H
