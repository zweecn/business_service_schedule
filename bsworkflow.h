#ifndef BSWORKFLOW_H
#define BSWORKFLOW_H

#include <QList>
#include <QQueue>

#include "bssnode.h"
#include "bsresource.h"
#include "bsrequirement.h"
#include "bsinstance.h"
#include "bssnodeplan.h"

class BSWorkFlow
{
public:
    static BSWorkFlow * Instance();
    void reset();

    int getResourcePrice(int period, int resType);
    int getResourcePrice(int period, int instanceID, int sNodeID);
    int getResourceTotalQLevel(int peroid, int resType);
    int getResourceQLevel(int period, int instanceID, int resType);
    int getRequirementQLevel(int period, int instanceID);
    int getRequirementWTP(int period, int instanceID);
    int getRequirementTotalQLevel(int period);
    int getUnitRequirementResourceCost(int period);
    int getRequirementFreeQLevel(int period);
    int getSNodeUnitQLevel(int resType);
    int getSNodeConcurrencyType(int sNodeID);
    int getResourceTypeSize();

    void reduceRequirement(int instanceID, int qLevel);
    void reduceResource(int period, int resType, int qlevel);
    void addResource(int period, int resType, int qlevel);
    void setResourceQLevel(int period, int resType, int totalQLevel);

    void showWorkFlowInfo();
    void showInstanceList();
    void showRequirementQueue();
    void showSNodeList();
    void showResourceList();

    QList<BSSNode> bsSNodeList;
    QList<BSResource> bsResourceList;
    QQueue<BSRequirement> bsRequirementQueue;
    QList<BSInstance> bsInstanceList;

protected:
    BSWorkFlow();
    static BSWorkFlow * _instance;

private:

    bool readBSSNodeList();
    bool readBSResourceList();
    bool readBSRequirementQueue();
    bool readBSInstanceList();

    int nodeSize;
    int resourceSize;
    int requirementSize;
    int instanceSize;
};


#endif // BSWORKFLOW_H
