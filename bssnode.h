#ifndef BSSNODE_H
#define BSSNODE_H

#include <QString>

class BSSNode
{
public:
    BSSNode();

    QString toString();

    int sid;
    int resType;
    int unitReqQLevel;
    int concurrencyType;
};

#endif // BSSNODE_H
