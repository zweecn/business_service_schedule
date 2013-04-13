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
    else if (this->eventType == BSEvent::RESOURCE_REDUCE_E4)
    {
        res += QString("Type:%1 ResType:%2 Amt:%3")
                .arg("RESOURCE_REDUCE_E4")
                .arg(this->e4Info.resType)
                .arg(this->e4Info.vQlevel);
    }
    else if (this->eventType == BSEvent::SERVICE_EXEC_DELAY_E5)
    {
        res += QString("Type:%1 Ins:%2 SNode:%3 TimeDelay:%4")
                .arg("SERVICE_EXEC_DELAY_E5")
                .arg(this->e5Info.instanceID)
                .arg(this->e5Info.sNodeID)
                .arg(this->e5Info.timeDelay);
    }

    res = res.trimmed().append("]");
    return res;
}
