#ifndef BSVARIATION_H
#define BSVARIATION_H

#include <QString>

class BSVariation
{
public:
    BSVariation();
    QString toString();

    int instanceID;
    int reqVLevel;
    int newReq;
    int resType;
    int vQlevel;
    int sNodeID;
    int timeDelay;
};

#endif // BSVARIATION_H
