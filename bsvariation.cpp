#include "bsvariation.h"


BSVariation::BSVariation()
{
    instanceID = reqVLevel = newReq = resType = vQlevel = sNodeID = timeDelay = 0;
}

QString BSVariation::toString()
{
    QString res = QString("instanceID:%1 reqVLevel%2 newReq%3 resType:%4 vQlevel:%5 sNodeID:%6 timeDelay:%7")
            .arg(instanceID)
            .arg(reqVLevel)
            .arg(newReq)
            .arg(resType)
            .arg(vQlevel)
            .arg(sNodeID)
            .arg(timeDelay);
    return res;
}

