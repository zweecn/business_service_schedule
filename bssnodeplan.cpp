#include "bssnodeplan.h"

BSSNodePlan::BSSNodePlan()
{
    snodeID = -1;
    startTime = -1;
    endTime = -1;
}

QString BSSNodePlan::toString()
{
    QString res = QString("%1:%2->%3")
            .arg(this->snodeID)
            .arg(this->startTime)
            .arg(this->endTime);
    return res;
}
