#include "bsresourceamountadd.h"

BSResourceAmountAdd::BSResourceAmountAdd()
{
}

QString BSResourceAmountAdd::toString()
{
    QString res = QString("ResAmtAdd:");

    for (int i = 0; i < addList.size(); i++)
    {
        res += QString("(Res:%1 Amt:%2)").arg(addList[i].resourceID).arg(addList[i].amount);
    }

    return res;
}
