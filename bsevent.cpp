#include "bsevent.h"

BSEvent::BSEvent()
{
}

QString BSEvent::toString()
{
    QString res = QString("Event: time:%1 type:%2 %3").arg(this->time)
            .arg(this->eventType)
            .arg("");
    return res;
}
