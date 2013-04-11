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

    enum
    {
        INDEPENDENT_NODE = 0,
        SYNC_NODE = 1
    };
};

#endif // BSSNODE_H
