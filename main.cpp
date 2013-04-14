#include <QtGui/QApplication>
#include <QDebug>
#include <QBitArray>
#include <climits>
#include <iostream>

#include "bsmainwidget.h"
#include "bsworkflow.h"
#include "singleton.h"
#include "bsconfig.h"
#include "bsevent.h"
#include "bsaction.h"
#include "bsalgorithm.h"
#include "bsinstance.h"
#include "bssnodeplan.h"

int main(int argc, char *argv[])
{
//    QApplication a(argc, argv);
//    BSMainWidget w;
//    w.show();
//    return a.exec();

    BSAlgorithm alg;
    BSEvent event;
    BSAction action;

//    /* Test E1 �˿�����ȡ��/����
//     * 1. ȡ�����������ڳ�������Դ����fork��һ��ʵ��
//     *    �����¼���ʱ����ͬ��ʱ��֮��ֻ�ܲ���Ϊ
//     */
//    qDebug() << "E1, ignore...";
//    event.eventType = BSEvent::REQUIREMENT_CANCEL_REDUCE_E1;
//    event.time = 11; //Mark
//    event.e1Info.instanceID = 2;
//    event.e1Info.reqVLevel = 1;
//    action = alg.schedule(event, true);
//    qDebug() << "The result is:";
//    qDebug() << event.toString();
//    qDebug() << action.toString() << "\n";

//    /* Test E1 �˿�����ȡ��/����
//     * 2. ȡ�����������ڳ�������Դ��fork��һ��ʵ��,����ȡ����ʱ����ͬ��ʱ��֮ǰ
//     */
//    qDebug() << "E1, fork...";
//    event.eventType = BSEvent::REQUIREMENT_CANCEL_REDUCE_E1;
//    event.time = 1; //Mark
//    event.e1Info.instanceID = 0;
//    event.e1Info.reqVLevel = 3;
//    action = alg.schedule(event, true);
//    qDebug() << "The result is:";
//    qDebug() << event.toString();
//    qDebug() << action.toString() << "\n";


//    /* Test E2 �˿���������
//     * 1. ����Ҫ��������ԴǨ�ƹ�������ѡ��Դ���Ѿ��㹻ִ��������Դ������
//     */
//    qDebug() << "E2, resource add...";
//    event.eventType = BSEvent::REQUIREMENT_ADD_E2;
//    event.time = 1;
//    event.e2Info.instanceID = 2;
//    event.e2Info.reqVLevel = 1; // Mark
//    event.e2Info.extraWTP = 2000;
//    action = alg.schedule(event, true);
//    qDebug() << "The result is:";
//    qDebug() << event.toString();
//    qDebug() << action.toString() << "\n";

//    /* Test E2 �˿���������
//     * 2. ��ǰ������Դ������������һ���ں�ѡ��Դ�㹻������fork��ʵ������һ����
//     */
//    qDebug() << "E2, fork to next...";
//    event.eventType = BSEvent::REQUIREMENT_ADD_E2;
//    event.time = 1;
//    event.e2Info.instanceID = 2;
//    event.e2Info.reqVLevel = 2; // Mark
//    event.e2Info.extraWTP = 2000;
//    action = alg.schedule(event, true);
//    qDebug() << "The result is:";
//    qDebug() << event.toString();
//    qDebug() << action.toString() << "\n";

//    /* Test E2 �˿���������
//     * 3. ��ǰ������Դ��������һ������ԴҲ������ֻ�ܽ�����Դת��
//     */
//    qDebug() << "E2, resource trans...";
//    event.eventType = BSEvent::REQUIREMENT_ADD_E2;
//    event.time = 1;
//    event.e2Info.instanceID = 2;
//    event.e2Info.reqVLevel = 2; // Mark
//    event.e2Info.extraWTP = 2000;
//    BSWorkFlow::Instance()->setResourceQLevel(1, 1, 0);
//    action = alg.schedule(event, true);
//    qDebug() << "The result is:";
//    qDebug() << event.toString();
//    qDebug() << action.toString() << "\n";

//    /* Test E3 �����˿�����
//     * 1. ��������Դ�㹻�ڵ�ǰ����fork��ʵ�������㣬������ڵ�ǰ����
//     */
//    event.eventType = BSEvent::REQUIREMENT_NEW_E3;
//    event.time = 1;
//    event.e3Info.instanceID = 2;
//    event.e3Info.requirement.setFree(false);
//    event.e3Info.requirement.customer = BSWorkFlow::Instance()->bsRequirementQueue.size();
//    event.e3Info.requirement.qLevel = 1; //Mark
//    event.e3Info.requirement.wtp = 1000;
//    action = alg.schedule(event, true);
//    qDebug() << "The result is:";
//    qDebug() << event.toString();
//    qDebug() << action.toString() << "\n";

//    /* Test E3 �����˿�����
//     * 2. ��������Դ�����������ڵ�ǰ�������㣬��ô���Ƴٵ���һ����fork
//     *   ����extraWTPҪ�㹻�����򲻹��ӳ��⳥
//     */
//    event.eventType = BSEvent::REQUIREMENT_NEW_E3;
//    event.time = 1;
//    event.e3Info.instanceID = 2;
//    event.e3Info.requirement.setFree(false);
//    event.e3Info.requirement.customer = BSWorkFlow::Instance()->bsRequirementQueue.size();
//    event.e3Info.requirement.qLevel = 2; //Mark
//    event.e3Info.requirement.wtp = 2000; //Mark
//    action = alg.schedule(event, true);
//    qDebug() << "The result is:";
//    qDebug() << event.toString();
//    qDebug() << action.toString() << "\n";

//    /* Test E3 �����˿�����
//     * 3. �����ں���һ���ڵ���Դ��������ֻ�ܲ���Ϊ
//     *   ���߸���extraWTP������ֻ���ڲ���Ϊ
//     */
//    event.eventType = BSEvent::REQUIREMENT_NEW_E3;
//    event.time = 1;
//    event.e3Info.instanceID = 2;
//    event.e3Info.requirement.setFree(false);
//    event.e3Info.requirement.customer = BSWorkFlow::Instance()->bsRequirementQueue.size();
//    event.e3Info.requirement.qLevel = 3; //Mark
//    event.e3Info.requirement.wtp = 1000; //Mark
//    action = alg.schedule(event, true);
//    qDebug() << "The result is:";
//    qDebug() << event.toString();
//    qDebug() << action.toString() << "\n";

    /* Test E4 �����˿�����
     * 3. �����ں���һ���ڵ���Դ��������ֻ�ܲ���Ϊ
     *   ���߸���extraWTP������ֻ���ڲ���Ϊ
     */
//    event.eventType = BSEvent::RESOURCE_REDUCE_E4;
//    event.time = 10;
//    event.e4Info.resType = 2;
//    event.e4Info.vQlevel = 56;

    // All is infruence
//    event.eventType = BSEvent::SERVICE_EXEC_DELAY_E5;
//    event.time = 10;
//    event.e5Info.instanceID = 1;
//    event.e5Info.sNodeID = 1;
//    event.e5Info.timeDelay = 10;

//    // Cur is infruence
//    event.eventType = BSEvent::SERVICE_EXEC_DELAY_E5;
//    event.time = 10;
//    event.e5Info.instanceID = 1;
//    event.e5Info.sNodeID = 1;
//    event.e5Info.timeDelay = 1;

// No NEED RETRY
//    event.eventType = BSEvent::SERVICE_EXEC_FAILED_E6;
//    event.time = 10;
//    event.e6Info.instanceID = 1;
//    event.e6Info.sNodeID = 2;
//    BSAction action = alg.schedule(event);

    // Need retry
//    event.eventType = BSEvent::SERVICE_EXEC_FAILED_E6;
//    event.time = 10;
//    event.e6Info.instanceID = 1;
//    event.e6Info.sNodeID = 1;

//    action = alg.schedule(event);

//    qDebug() << "\nThe result is:";
//    qDebug() << event.toString();
//    qDebug() << action.toString() << "\n";


    BSWorkFlow::Instance()->showSNodeList();
    BSWorkFlow::Instance()->showResourceList();
    BSWorkFlow::Instance()->showInstanceList();
    BSWorkFlow::Instance()->showRequirementQueue();

    return 0;
}
