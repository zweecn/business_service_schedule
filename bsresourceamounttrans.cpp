#include "bsresourceamounttrans.h"

BSResourceAmountTrans::BSResourceAmountTrans()
{
}

QString BSResourceAmountTrans::toString()
{
    QString res = QString("ResAmtTrans:");
    for (int i = 0; i < transList.size(); i++)
    {
        res += QString("(Ins:%1 Res:%2 Amt:%3)").arg(transList[i].instanceID)
                .arg(transList[i].resourceID)
                .arg(transList[i].amount);
    }
    return res;
}
