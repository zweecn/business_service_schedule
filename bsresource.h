#ifndef BSRESOURCE_H
#define BSRESOURCE_H

#include <QString>

class BSResource
{
public:
    BSResource();

    QString toString();

    int period;
    int resType;
    int totalQLevel;
    int price;
};

#endif // BSRESOURCE_H
