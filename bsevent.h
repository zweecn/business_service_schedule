#ifndef BSEVENT_H
#define BSEVENT_H

#include <QString>

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
    int newReq;
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

class BSEvent
{
public:
    BSEvent();
    QString toString();

    int time;
    int eventType;
    E1Info e1Info;
    E2Info e2Info;
    E3Info e3Info;
    E4Info e4Info;
    E5Info e5Info;

    enum
    {
        NOT_EVENT = -1,
        REQUIREMENT_CANCEL_REDUCE_E1,
        REQUIREMENT_ADD_E2
    };
};

#endif // BSEVENT_H
