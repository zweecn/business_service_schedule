#ifndef BSEVENT_H
#define BSEVENT_H

#include <QString>
#include <QList>

#include "bsrequirement.h"

// Requirement reduce / cancel
struct E1Info
{
    int instanceID;
    int reqVLevel;
};

// Requirement add
struct E2Info
{
    int instanceID;
    int reqVLevel;
    int extraWTP;
};

// New requirement
struct E3Info
{
    int instanceID; //这里其实无用，只是为了取同步结点
    BSRequirement requirement;
};

// Resource changed
struct E4Info
{
    int resType;
    int vQlevel;
};

// Delay
struct E5Info
{
    int instanceID;
    int sNodeID;
    int timeDelay;
};

// Failed
struct E6Info
{
    int instanceID;
    int sNodeID;
};

class BSEvent
{
public:
    BSEvent();
    QString name();
    QString toString();

    static QList<BSEvent> randomEvent();

    int eventTime;
    int eventType;
    E1Info e1Info;
    E2Info e2Info;
    E3Info e3Info;
    E4Info e4Info;
    E5Info e5Info;
    E6Info e6Info;

    enum
    {
        NOT_EVENT = -1,
        REQUIREMENT_CANCEL_REDUCE_E1,
        REQUIREMENT_ADD_E2,
        REQUIREMENT_NEW_E3,
        RESOURCE_REDUCE_E4,
        SERVICE_EXEC_DELAY_E5,
        SERVICE_EXEC_FAILED_E6,
        EVENT_SIZE = 6
    };
};

#endif // BSEVENT_H
