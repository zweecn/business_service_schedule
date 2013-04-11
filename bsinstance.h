#ifndef BSINSTANCE_H
#define BSINSTANCE_H

#include <QList>

#include "bsrequirement.h"
#include "bssnodeplan.h"

class BSInstance
{
public:
    BSInstance();

    QString toString();

    int instanceID;
    int requirementID;
    QList<BSSNodePlan> sNodePlanList;
};

#endif // BSINSTANCE_H
