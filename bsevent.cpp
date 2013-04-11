#include "bsevent.h"

BSEvent::BSEvent()
{
}

QString BSEvent::toString()
{
    QString res = QString("[Event: Time:%1 ")
            .arg(this->time);
    if (this->eventType == BSEvent::REQUIREMENT_CANCEL_REDUCE_E1)
    {
        res += QString("Type:%1 Ins:%2 ReqVLevel:%3")
                .arg("REQUIREMENT_CANCEL_REDUCE_E1")
                .arg(this->e1Info.instanceID)
                .arg(this->e1Info.reqVLevel);
    }
    else if (this->eventType == BSEvent::REQUIREMENT_ADD_E2)
    {
        res += QString("Type:%1 Ins:%2 ReqVLevel:%3")
                .arg("REQUIREMENT_ADD_E2")
                .arg(this->e1Info.instanceID)
                .arg(this->e1Info.reqVLevel);
    }

    res = res.trimmed().append("]");
    return res;
}
