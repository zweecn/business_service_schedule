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
private:
    Engine *ep;
};

#endif // TEST_H
