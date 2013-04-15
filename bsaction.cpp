#include <climits>
#include <QDebug>

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
    else if (this->aType == BSAction::CANCEL_INSTANCE)
    {
        res += QString(" Type:%1 (CancelIns:")
                .arg("CANCEL_INSTANCE");
        for (int i = 0; i < cancelInstanceInfo.instanceIDList.size(); i++)
        {
            res += QString(" %1").arg(cancelInstanceInfo.instanceIDList[i]);
        }
        res += QString(") (FreeRes:");
        for (int i = 0; i < cancelInstanceInfo.freeResourceList.size(); i++)
        {
            res += QString(" type:%1 Amt:%2")
                    .arg(cancelInstanceInfo.freeResourceList[i].resourceType)
                    .arg(cancelInstanceInfo.freeResourceList[i].amount);
        }
        res += QString(")");
        res += QString("NeedAddRes:%1 Amt:%2")
                .arg(cancelInstanceInfo.resourceAdd.resourceType)
                .arg(cancelInstanceInfo.resourceAdd.amount);
    }
    else if (this->aType == BSAction::RETRY_SERVICE)
    {
        res += QString(" Type:%1 Ins:%2 SNode:%3")
                .arg("RETRY_SERVICE")
                .arg(retryInstanceInfo.instanceID)
                .arg(retryInstanceInfo.sNodeID);
    }
    else if (this->aType == BSAction::FORK_TO_NEXT_PEROID)
    {
        res += QString(" Type:%1 Ins:%2 NextReq:%3")
                .arg("FORK_TO_NEXT_PEROID")
                .arg(delayToNextPeriodInfo.instanceID)
                .arg(delayToNextPeriodInfo.nextRequirement.toString());
        res += QString(") (FreeRes:");
        for (int i = 0; i < delayToNextPeriodInfo.freeResourceList.size(); i++)
        {
            res += QString(" type:%1 Amt:%2")
                    .arg(delayToNextPeriodInfo.freeResourceList[i].resourceType)
                    .arg(delayToNextPeriodInfo.freeResourceList[i].amount);
        }
        res += QString(")");
    }
    else if (this->aType == BSAction::CANCEL_DELAY_NEXT_PEROID)
    {
        res += QString(" Type:%1 (CancelIns:")
                .arg("CANCEL_DELAY_NEXT_PEROID");
        for (int i = 0; i < cancelAndDelayInstanceInfo.instanceIDList.size(); i++)
        {
            res += QString(" %1").arg(cancelAndDelayInstanceInfo.instanceIDList[i]);
        }
        res += QString(") (FreeOrNeedRes:");
        for (int i = 0; i < cancelAndDelayInstanceInfo.freeOrNeedResourceList.size(); i++)
        {
            res += QString(" type:%1 Amt:%2")
                    .arg(cancelAndDelayInstanceInfo.freeOrNeedResourceList[i].resourceType)
                    .arg(cancelAndDelayInstanceInfo.freeOrNeedResourceList[i].amount);
        }
        res += QString(")");
        res += QString("NeedAddRes:%1 Amt:%2")
                .arg(cancelAndDelayInstanceInfo.resourceAdd.resourceType)
                .arg(cancelAndDelayInstanceInfo.resourceAdd.amount);
    }
    res += QString(" Reward:%2]").arg(this->reward);
    return res;
}
