#ifndef BSCONFIG_H
#define BSCONFIG_H

#include <QMap>

class BSConfig
{
public:
    static BSConfig * Instance();

    int getUnitRPrice();
    int getUnitCompensatePrice();
    int getUnitDelayCost();
    int getUnitRCancelCost();
    int getUnitTimeDelayCost();
protected:
    BSConfig();
    static BSConfig* _instance;
private:
    bool init();
    QMap<QString, QString> confMap;

};

#endif // BSCONFIG_H
