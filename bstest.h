#ifndef BSTEST_H
#define BSTEST_H

#include <engine.h>

class BSTest
{
public:
    BSTest();
    ~BSTest();

    void runTest1();
    void runTest2();
    void runTest3();
private:
    Engine *ep;
};

#endif // TEST_H
