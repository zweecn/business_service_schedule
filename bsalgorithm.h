#ifndef BSALGORITHM_H
#define BSALGORITHM_H

#include "bsevent.h"
#include "bsaction.h"

class BSAlgorithm
{
public:
    BSAlgorithm();

    BSAction schedule(const BSEvent & event);

private:
    BSAction subScheduleE1(const BSEvent & event);
    BSAction forkNewInstance(int currInstanceID, int freeReqVLevel);

};

#endif // BSALGORITHM_H
