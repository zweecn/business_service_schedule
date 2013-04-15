#ifndef BSALGORITHM_H
#define BSALGORITHM_H

#include <QList>

#include "bsevent.h"
#include "bsaction.h"

class BSAlgorithm
{
public:
    BSAlgorithm();

    BSAction schedule(const BSEvent & event, bool printAllAction);

private:
    QList<BSAction> subScheduleE1(const BSEvent & event);
    QList<BSAction> subScheduleE2(const BSEvent & event);
    QList<BSAction> subScheduleE3(const BSEvent & event);
    QList<BSAction> subScheduleE4(const BSEvent & event);
    QList<BSAction> subScheduleE5(const BSEvent & event);
    QList<BSAction> subScheduleE6(const BSEvent & event);

    BSAction forkNewInstance(int time, int currInstanceID, int freeReqVLevel);
    BSAction forkNewInstance(int time, int currInstanceID, int addReqVLevel, int extraWTP);
    BSAction addResource(int addReqVLevel, int extraWTP);
    BSAction transResource(int addReqVLevel, int extraWTP);
    BSAction cancelInstances(int time, int resType, int vQLevel);
    BSAction cancelInstance(int time, int instanceID);
    BSAction retryInstance(int instanceID, int sNodeID);
    BSAction forkNextPeriod(int time, int instanceID, int newQlevel, int extraWTP);
    BSAction delayNextPeriod(int time, int instanceID);
    BSAction delayNextPeriod(int time, int instanceID, const BSRequirement & req);
    BSAction cancelAndDelayNextPeriod(int time, int resType, int vQLevel);

    QList<ResourceNode> freeResource(int time, QList<int> & chouseInstance, int exceptResType);
    QList<int> isOne(int num);
    int addResourceTotalPrice(int addReqVLevel);
    int addResourceTotalPrice(int addReqVLevel, ResourceAddInfo & addInfo);

};

#endif // BSALGORITHM_H
