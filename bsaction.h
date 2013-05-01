#ifndef BSACTION_H
#define BSACTION_H

#include <QString>

#include "bsinstance.h"

struct IgnoreInfo
{
};

struct ForkInfo
{
    int requirementID;
    BSInstance instance;
};

struct ResourceAddNode
{
    int resourceType;
    int amount;
};

struct ResourceAddInfo
{
    QList<ResourceAddNode> resourceAddList;
};

struct ResourceTransNode
{
    int instanceID;
    int qLevel;
};

struct ResourceTransInfo
{
    QList<ResourceTransNode> resourceTransList;
    QList<ResourceAddNode> resourceAddList;
};

struct ResourceNode
{
    int resourceType;
    int amount;
};

struct CancelInstanceInfo
{
    QList<int> instanceIDList;
    QList<ResourceNode> freeResourceList;
    ResourceNode resourceAdd;
};

struct CancelToDelayInstanceInfo
{
    QList<int> instanceIDList;
    QList<ResourceNode> freeOrNeedResourceList;
    ResourceNode resourceAdd;
};

struct RetryInstanceInfo
{
    int instanceID;
    int sNodeID;
};

struct DelayToNextPeriodInfo
{
    int instanceID;
    int beforeRequirementID;
    BSRequirement nextRequirement;
    QList<ResourceNode> freeResourceList;
};

struct ForkToNextPeriodInfo
{
    int instanceID;
    BSRequirement nextRequirement;
    QList<ResourceNode> freeResourceList;

    ForkToNextPeriodInfo & operator =(const ForkToNextPeriodInfo & other)
    {
        if (this == &other)
        {
            return *this;
        }
        this->instanceID = other.instanceID;
        this->nextRequirement = other.nextRequirement;
        this->freeResourceList = other.freeResourceList;
        return *this;
    }

    ForkToNextPeriodInfo & operator =(const DelayToNextPeriodInfo & other)
    {
        this->instanceID = other.instanceID;
        this->nextRequirement = other.nextRequirement;
        this->freeResourceList = other.freeResourceList;
        return *this;
    }
};


class BSAction
{
public:
    BSAction();
    QString name();
    QString toString();

    int aid;
    int aType;
    int revenue;
    int cost;
    int profit;

    IgnoreInfo ignoreInfo;
    ForkInfo forkInfo;
    ForkToNextPeriodInfo forkToNextPeriodInfo;
    ResourceAddInfo resourceAddInfo;
    ResourceTransInfo resourceTransInfo;
    CancelInstanceInfo cancelInstanceInfo;
    RetryInstanceInfo retryInstanceInfo;
    DelayToNextPeriodInfo delayToNextPeriodInfo;
    CancelToDelayInstanceInfo cancelToDelayInstanceInfo;

    enum
    {
        IGNORE,
        FORK_INSTANCE,
        FORK_NEXT_PERIOD,
        RESOURCE_ADD_PLAN,
        RESOURCE_TRANS_PLAN,
        CANCEL_INSTANCE,
        RETRY_SERVICE,
        DELAY_TO_NEXT_PEROID,
        CANCEL_DELAY_NEXT_PEROID
    };
};

#endif // BSACTION_H
