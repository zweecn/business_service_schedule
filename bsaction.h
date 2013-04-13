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
};

class BSAction
{
public:
    BSAction();

    QString toString();

    int aid;
    int aType;
    int reward;

    IgnoreInfo ignoreInfo;
    ForkInfo forkInfo;
    ResourceAddInfo resourceAddInfo;
    ResourceTransInfo resourceTransInfo;
    CancelInstanceInfo cancelInstanceInfo;

    enum
    {
        IGNORE,
        FORK_INSTANCE,
        RESOURCE_ADD_PLAN,
        RESOURCE_TRANS_PLAN,
        CANCEL_INSTANCE
    };
};

#endif // BSACTION_H
