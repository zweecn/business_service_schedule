#ifndef BSACTION_H
#define BSACTION_H

#include <QString>

#include "bsresourceamountadd.h"
#include "bsresourceamounttrans.h"
#include "bsinstance.h"

struct IgnoreInfo
{
};

struct ForkInfo
{
    int requirementID;
    BSInstance instance;
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

    enum
    {
        IGNORE,
        FORK_INSTANCE
    };
};

#endif // BSACTION_H
