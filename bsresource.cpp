#include "bsresource.h"

BSResource::BSResource()
{
    period = -1;
    resType = -1;
    totalQLevel = -1;
    price = -1;
}

QString BSResource::toString()
{
    QString res = QString("[Resource: Period:%1 ResType:%2 TotalQLevel:%3 Price:%4]")
            .arg(this->period)
            .arg(this->resType)
            .arg(this->totalQLevel)
            .arg(this->price);

    return res;
}
