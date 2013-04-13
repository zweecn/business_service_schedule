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

    int getResourcePrice(int period, int resType);
    int getResourceTotalQLevel(int peroid, int resType);
    int getRequirementQLevel(int period, int instanceID);
    int getRequirementWTP(int period, int instanceID);
    int getRequirementTotalQLevel(int period);
    int getSNodeUnitQLevel(int resType);

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
