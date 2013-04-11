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
    if (this->aType == BSAction::FORK_INSTANCE)
    {
        res += QString(" Type:%1 Ins:%2")
                .arg("FORK_INSTANCE")
                .arg(this->forkInfo.instance.toString());
    }
    res += QString(" Reward:%2]").arg(this->reward);
    return res;
}
