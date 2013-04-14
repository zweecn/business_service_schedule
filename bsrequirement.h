#ifndef BSREQUIREMENT_H
#define BSREQUIREMENT_H

#include <QString>

class BSRequirement
{
public:
    BSRequirement();

    QString toString();
    void reset();
    void setFree(bool _free);
    bool isFree();

    int customer;
    int qLevel;
    int expectedPeriod;
    int wtp;

private:
    bool free;

};

#endif // BSREQUIREMENT_H
