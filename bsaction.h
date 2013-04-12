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

    enum
    {
        IGNORE,
        FORK_INSTANCE,
        RESOURCE_ADD_PLAN,
        RESOURCE_TRANS_PLAN
    };
};

#endif // BSACTION_H
