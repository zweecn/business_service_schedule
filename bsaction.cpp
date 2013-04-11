#include <climits>

#include "bsaction.h"

BSAction::BSAction()
{
    aid = 0;
    aType = IGNORE;
    reward = -INT_MAX;

//    faultInstanceID = 0;
//    faultSID = 0;
//    newRequirementID = 0;
//    instanceFork = 0;
//    period = 0;
//    cancelIID = 0;
//    delayIID = 0;
//    retrySID = 0;
}

QString BSAction::toString()
{
//    QString res = QString("[AID:%1 AType:%2 FtInsID:%3 FtSID:%4 newReqID:%5 InsFk:%6 Prd:%7 CanIID:%8 DeIID:%9 ReSID:%10 Reward:%11")
//            .arg(aid)
//            .arg(aType)
//            .arg(faultInstanceID)
//            .arg(faultSID)
//            .arg(newRequirementID)
//            .arg(instanceFork)
//            .arg(period)
//            .arg(cancelIID)
//            .arg(delayIID)
//            .arg(retrySID)
//            .arg(reward);

//    res += QString(" %1 %2]")
//            .arg(resourceAmountAdd.toString())
//            .arg(resourceAmountTrans.toString());

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
