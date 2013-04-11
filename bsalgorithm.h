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
    BSAction subScheduleE2(const BSEvent & event);
    BSAction forkNewInstance(int time, int currInstanceID, int freeReqVLevel);
    BSAction forkNewInstance(int time, int currInstanceID, int addReqVLevel, int extraWTP);
    BSAction addResource(int addReqVLevel, int extraWTP);

};

#endif // BSALGORITHM_H
