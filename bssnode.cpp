#include "bssnode.h"

BSSNode::BSSNode()
{
}

QString BSSNode::toString()
{
    QString res = QString("[SNode:%1 ResType:%2 UnitReqQLevel:%3 ConType:%4]")
            .arg(this->sid)
            .arg(this->resType)
            .arg(this->unitReqQLevel)
            .arg(this->concurrencyType);

    return res;
}
