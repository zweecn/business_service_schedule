#include "bsinstance.h"

BSInstance::BSInstance()
{
    instanceID = -1;
    requirementID = -1;
}

QString BSInstance::toString()
{
    QString res = QString("[Instance:%1 Requirement:%2").arg(this->instanceID).arg(this->requirementID);
    for (int i = 0; i < sNodePlanList.size(); i++)
    {
        res += " " + sNodePlanList[i].toString();
    }
    res += "]";
    return res;
}
