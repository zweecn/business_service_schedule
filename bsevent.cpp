#include "bsevent.h"

BSEvent::BSEvent()
{
    time = -1;
    eventType = BSEvent::NOT_EVENT;
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
        res += QString("Type:%1 Ins:%2 ReqVLevel:%3 extraWTP:%4")
                .arg("REQUIREMENT_ADD_E2")
                .arg(this->e2Info.instanceID)
                .arg(this->e2Info.reqVLevel)
                .arg(this->e2Info.extraWTP);
    }
    else if (this->eventType == BSEvent::REQUIREMENT_NEW_E3)
    {
        res += QString("Type:%1 Ins:%2 Req:%3")
                .arg("REQUIREMENT_NEW_E3")
                .arg(this->e3Info.instanceID)
                .arg(this->e3Info.requirement.toString());
    }

    res = res.trimmed().append("]");
    return res;
}
