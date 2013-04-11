#ifndef BSRESOURCEAMOUNTADD_H
#define BSRESOURCEAMOUNTADD_H

#include <QList>
#include <QString>

struct BSResourceAmountAddNode
{
    int resourceID;
    int amount;
};

class BSResourceAmountAdd
{
public:
    BSResourceAmountAdd();
    QString toString();

    QList<BSResourceAmountAddNode> addList;
};

#endif // BSRESOURCEAMOUNTADD_H
