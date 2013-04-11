#ifndef BSRESOURCEAMOUNTTRANS_H
#define BSRESOURCEAMOUNTTRANS_H

#include <QList>
#include <QString>

struct BSResourceAmountTransNode
{
    int instanceID;
    int resourceID;
    int amount;
};

class BSResourceAmountTrans
{
public:
    BSResourceAmountTrans();
    QString toString();

    QList<BSResourceAmountTransNode> transList;
};

#endif // BSRESOURCEAMOUNTTRANS_H
