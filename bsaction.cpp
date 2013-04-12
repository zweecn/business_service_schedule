#include <climits>

#include "bsaction.h"

BSAction::BSAction()
{
    aid = 0;
    aType = IGNORE;
    reward = -INT_MAX;
}

QString BSAction::toString()
{
    QString res = QString("[Action:%1").arg(aid);
    if (this->aType == BSAction::IGNORE)
    {
        res += QString(" Type:%1").arg("IGNORE");
    }
    else if (this->aType == BSAction::FORK_INSTANCE)
    {
        res += QString(" Type:%1 Ins:%2")
                .arg("FORK_INSTANCE")
                .arg(this->forkInfo.instance.toString());
    }
    else if (this->aType == BSAction::RESOURCE_ADD_PLAN)
    {
        res += QString(" Type:%1 ")
                .arg("RESOURCE_ADD_PLAN");
        for (int i = 0; i < resourceAddInfo.resourceAddList.size(); i++)
        {
            res += QString("Res:%1 Amt:%2 ")
                    .arg(resourceAddInfo.resourceAddList[i].resourceType)
                    .arg(resourceAddInfo.resourceAddList[i].amount);
        }
    }
    else if (this->aType == BSAction::RESOURCE_TRANS_PLAN)
    {
        res += QString(" Type:%1 ")
                .arg("RESOURCE_TRANS_PLAN");
        for (int i = 0; i < resourceTransInfo.resourceTransList.size(); i++)
        {
            res += QString("Ins:%1 QLevel:%2 ")
                    .arg(resourceTransInfo.resourceTransList[i].instanceID)
                    .arg(resourceTransInfo.resourceTransList[i].qLevel);
        }
        for (int i = 0; i < resourceTransInfo.resourceAddList.size(); i++)
        {
            res += QString("Res:%1 Amt:%2 ")
                    .arg(resourceTransInfo.resourceAddList[i].resourceType)
                    .arg(resourceTransInfo.resourceAddList[i].amount);
        }
    }
    res += QString(" Reward:%2]").arg(this->reward);
    return res;
}
