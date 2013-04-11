#ifndef BSSNODEPLAN_H
#define BSSNODEPLAN_H

#include <QString>

class BSSNodePlan
{
public:
    BSSNodePlan();

    QString toString();

    int snodeID;
    int startTime;
    int endTime;
};

#endif // BSSNODEPLAN_H
