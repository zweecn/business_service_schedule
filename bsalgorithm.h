#ifndef BSALGORITHM_H
#define BSALGORITHM_H

#include <QList>

#include "bsevent.h"
#include "bsaction.h"

class BSAlgorithm
{
public:
    BSAlgorithm();

    BSAction schedule(const BSEvent & event);

private:
    QList<BSAction> subScheduleE1(const BSEvent & event);
    QList<BSAction> subScheduleE2(const BSEvent & event);

    BSAction forkNewInstance(int time, int currInstanceID, int freeReqVLevel);
    BSAction forkNewInstance(int time, int currInstanceID, int addReqVLevel, int extraWTP);
    BSAction addResource(int addReqVLevel, int extraWTP);
    BSAction transResource(int addReqVLevel, int extraWTP);

    QList<int> isOne(int num);
    int addResourceTotalPrice(int addReqVLevel);
    int addResourceTotalPrice(int addReqVLevel, ResourceAddInfo & addInfo);

};

#endif // BSALGORITHM_H
