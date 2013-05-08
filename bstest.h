#ifndef BSTEST_H
#define BSTEST_H

#include <engine.h>
#include <QString>

class BSTest
{
public:
    BSTest();
    ~BSTest();

    void runTest1();
    void runTest2();
    void runTest3();
    void saveMatlabCmd();

private:
    Engine *ep;
    QString cmd;
};

#endif // TEST_H
