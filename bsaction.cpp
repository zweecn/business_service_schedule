#include <climits>
#include <QDebug>

#include "bsaction.h"

BSAction::BSAction()
{
    aid = 0;
    aType = IGNORE;
    revenue = 0;
    cost = -INT_MAX;
    profit = -INT_MAX;
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
    else if (this->aType == BSAction::DELAY_TO_NEXT_PEROID)
    {
        res += QString(" Type:%1 Ins:%2 NextReq:%3")
                .arg("DELAY_TO_NEXT_PEROID")
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
    else if (this->aType == BSAction::FORK_NEXT_PERIOD)
    {
        res += QString(" Type:%1 Ins:%2 NextReq:%3")
                .arg("FORK_NEXT_PERIOD")
                .arg(forkToNextPeriodInfo.instanceID)
                .arg(forkToNextPeriodInfo.nextRequirement.toString());
        res += QString(") (FreeRes:");
        for (int i = 0; i < forkToNextPeriodInfo.freeResourceList.size(); i++)
        {
            res += QString(" type:%1 Amt:%2")
                    .arg(forkToNextPeriodInfo.freeResourceList[i].resourceType)
                    .arg(forkToNextPeriodInfo.freeResourceList[i].amount);
        }
        res += QString(")");
    }
    else if (this->aType == BSAction::CANCEL_DELAY_NEXT_PEROID)
    {
        res += QString(" Type:%1 (CancelIns:")
                .arg("CANCEL_DELAY_NEXT_PEROID");
        for (int i = 0; i < cancelToDelayInstanceInfo.instanceIDList.size(); i++)
        {
            res += QString(" %1").arg(cancelToDelayInstanceInfo.instanceIDList[i]);
        }
        res += QString(") (FreeOrNeedRes:");
        for (int i = 0; i < cancelToDelayInstanceInfo.freeOrNeedResourceList.size(); i++)
        {
            res += QString(" type:%1 Amt:%2")
                    .arg(cancelToDelayInstanceInfo.freeOrNeedResourceList[i].resourceType)
                    .arg(cancelToDelayInstanceInfo.freeOrNeedResourceList[i].amount);
        }
        res += QString(")");
        res += QString("NeedAddRes:%1 Amt:%2")
                .arg(cancelToDelayInstanceInfo.resourceAdd.resourceType)
                .arg(cancelToDelayInstanceInfo.resourceAdd.amount);
    }
    res += QString(" Revenue:%1 Cost:%2 Profit:%3]")
            .arg(this->revenue)
            .arg(this->cost)
            .arg(this->profit);
    return res;
}
