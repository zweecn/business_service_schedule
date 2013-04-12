#include "bsrequirement.h"

BSRequirement::BSRequirement()
{
    customer = -1;
    qLevel = -1;
    expectedPeriod = -1;
    wtp = -1;
}

QString BSRequirement::toString()
{
    QString res = QString("[Requirement:%1 Qlevel:%2 ExpPeriod:%3 wtp:%4]")
            .arg(this->customer)
            .arg(this->qLevel)
            .arg(this->expectedPeriod)
            .arg(this->wtp);

    return res;
}

void BSRequirement::setFree(bool _free)
{
    this->free = _free;
}

bool BSRequirement::isFree()
{
    return free;
}
