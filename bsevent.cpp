#include <cstdlib>
#include <ctime>
#include <QDebug>
#include <cassert>

#include "bsevent.h"
#include "bsworkflow.h"
#include "bsconfig.h"

BSEvent::BSEvent()
{
    eventTime = -1;
    eventType = BSEvent::NOT_EVENT;
}

QString BSEvent::name()
{
    if (this->eventType == BSEvent::REQUIREMENT_CANCEL_REDUCE_E1)
    {
         return ("E1:REQUIREMENT_CANCEL_REDUCE");
    }
    else if (this->eventType == BSEvent::REQUIREMENT_ADD_E2)
    {
        return ("E2:REQUIREMENT_ADD");
    }
    else if (this->eventType == BSEvent::REQUIREMENT_NEW_E3)
    {
        return ("E3:REQUIREMENT_NEW");
    }
    else if (this->eventType == BSEvent::RESOURCE_REDUCE_E4)
    {
        return ("E4:RESOURCE_REDUCE");
    }
    else if (this->eventType == BSEvent::SERVICE_EXEC_DELAY_E5)
    {
        return ("E5:SERVICE_EXEC_DELAY");
    }
    else if (this->eventType == BSEvent::SERVICE_EXEC_FAILED_E6)
    {
        return ("E6:SERVICE_EXEC_FAILED");
    }

    return ("NOT_EVENT");
}

QString BSEvent::toString()
{
    QString res = QString("[Event: Time:%1 ")
            .arg(this->eventTime);
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
    else if (this->eventType == BSEvent::SERVICE_EXEC_FAILED_E6)
    {
        res += QString("Type:%1 Ins:%2 SNode:%3")
                .arg("SERVICE_EXEC_FAILED_E6")
                .arg(this->e6Info.instanceID)
                .arg(this->e6Info.sNodeID);
    }
    else
    {
        res += QString("Type:%1").arg(eventType);
    }

    res = res.trimmed().append("]");
    return res;
}

QList<BSEvent> BSEvent::randomEvent()
{
    QList<BSEvent> eventList;
    int nodeSize = BSWorkFlow::Instance()->bsSNodeList.size();
    int insSize = BSWorkFlow::Instance()->bsInstanceList.size();
    int maxTime = 0;
    for (int i = 0; i < insSize; i++)
    {
        int t = BSWorkFlow::Instance()->bsInstanceList[i].sNodePlanList.last().endTime;
        if (maxTime < t)
        {
            maxTime = t;
        }
    }
    int seed = time(NULL);
    srand(seed);
    int reqID = BSWorkFlow::Instance()->bsRequirementQueue.size();
//    for (int nodeID = 0; nodeID < nodeSize; nodeID++)
    int eventTime = 0;
    for (int i = 0; i < nodeSize*2; i++)
    {
        int nodeID = i/2;
        BSEvent event;
        int instanceID = rand() % insSize;
        BSInstance & ins = BSWorkFlow::Instance()->bsInstanceList[instanceID];
        int startTime = ins.sNodePlanList[nodeID].startTime;
        int endTime = ins.sNodePlanList[nodeID].endTime;
        assert(endTime - startTime > 0);
        event.eventTime = eventTime = rand() % (endTime - startTime) + 2 + eventTime;
        event.eventType = rand() % EVENT_SIZE;

        if (event.eventType == BSEvent::REQUIREMENT_CANCEL_REDUCE_E1)
        {
            event.e1Info.instanceID = instanceID;
            int maxReqVLevel = BSWorkFlow::Instance()->getRequirementQLevel(0, instanceID);
            event.e1Info.reqVLevel = rand() % maxReqVLevel;
        }
        else if (event.eventType == BSEvent::REQUIREMENT_ADD_E2)
        {
            event.e2Info.instanceID = instanceID;
            event.e2Info.reqVLevel = rand() % 5;
            event.e2Info.extraWTP = (rand() % 10) * BSConfig::Instance()->getUnitRPrice();
        }
        else if (event.eventType == BSEvent::REQUIREMENT_NEW_E3)
        {
            event.e3Info.instanceID = instanceID;
            event.e3Info.requirement.customer = (reqID++);
            event.e3Info.requirement.expectedPeriod = 0;
            event.e3Info.requirement.setFree(true);
            event.e3Info.requirement.qLevel = rand() % 5;
            event.e3Info.requirement.wtp = (rand() % 10) * BSConfig::Instance()->getUnitRPrice();
        }
        else if (event.eventType == BSEvent::RESOURCE_REDUCE_E4)
        {
            event.e4Info.resType = rand() % BSWorkFlow::Instance()->getResourceTypeSize();
            int total = BSWorkFlow::Instance()->getResourceTotalQLevel(0, event.e4Info.resType);
            event.e4Info.vQlevel = (rand() % total + 1) * 2;
        }
        else if (event.eventType == BSEvent::SERVICE_EXEC_DELAY_E5)
        {
            event.e5Info.instanceID = instanceID;
            event.e5Info.sNodeID = nodeID;
            event.e5Info.timeDelay = rand() % 10;
        }
        else if (event.eventType == BSEvent::SERVICE_EXEC_FAILED_E6)
        {
            event.e6Info.instanceID = instanceID;
            event.e6Info.sNodeID = nodeID;
        }
        else
        {
            qDebug() << "NOT" << __FILE__ << __LINE__;
        }

//        qDebug() << event.toString();
        eventList.append(event);
    }

    return eventList;
}
