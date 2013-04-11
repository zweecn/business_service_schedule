#include <QQueue>

#include "bsalgorithm.h"
#include "bsworkflow.h"
#include "bsconfig.h"

BSAlgorithm::BSAlgorithm()
{
}

BSAction BSAlgorithm::schedule(const BSEvent &event)
{
    BSAction action;
    if (event.eventType == BSEvent::REQUIREMENT_CANCEL_E1)
    {
        return subScheduleE1(event);
    }
    return action;
}

BSAction BSAlgorithm::subScheduleE1(const BSEvent &event)
{
    BSAction ignoreAction;
    // [1] ��ǰ�˿�ȡ�����⳥
    ignoreAction.reward = BSConfig::Instance()->getUnitCompensatePrice()
            * event.e1Info.reqVLevel;
    // [2] ��ǰ�˿�ȡ���޷���ñ�׼�۸�
    ignoreAction.reward -= event.e1Info.reqVLevel * BSConfig::Instance()->getUnitRPrice();

    BSAction forkAction = forkNewInstance(event.e1Info.instanceID, event.e1Info.reqVLevel);

    if (ignoreAction.reward >= forkAction.reward)
    {
        return ignoreAction;
    }
    return forkAction;
}

BSAction BSAlgorithm::forkNewInstance(int currInstanceID, int freeReqVLevel)
{
    //Fork
    BSAction action;
    action.aType = BSAction::FORK_INSTANCE;
    BSInstance & ins = BSWorkFlow::Instance()->bsInstanceList[currInstanceID];
    QQueue<BSRequirement> & reqQueue = BSWorkFlow::Instance()->bsRequirementQueue;
    int wtp = 0;
    int req = -1;
    for (int i = 0; i < reqQueue.size(); i++)
    {
        if (wtp < reqQueue[i].wtp && reqQueue[i].qLevel <= freeReqVLevel)
        {
            wtp = reqQueue[i].wtp && reqQueue[i].qLevel;
            req = i;
        }
    }
    if (req != -1)
    {
        action.forkInfo.requirementID = req;
        action.forkInfo.instance.instanceID = BSWorkFlow::Instance()->bsInstanceList.size();
        action.forkInfo.instance.requirementID = req;
        action.forkInfo.instance.sNodePlanList = ins.sNodePlanList;
        // [1] fork�������µĶ���֧���ļ۸�
        action.reward = BSWorkFlow::Instance()->bsRequirementQueue[req].wtp;
        // [2] �µ�����ı�׼�۸�
        action.reward += BSWorkFlow::Instance()->bsRequirementQueue[req].qLevel
                * BSConfig::Instance()->getUnitRPrice();
        // [3] ��ǰ�˿�ȡ�����⳥
        action.reward += BSConfig::Instance()->getUnitCompensatePrice()
                * freeReqVLevel;
        // [4] ��ǰ�˿�ȡ���޷���ñ�׼�۸�
        action.reward -= freeReqVLevel * BSConfig::Instance()->getUnitRPrice();
    }

    return action;
}
