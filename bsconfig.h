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

    void setUnitRPrice(int _unitRPrice);
    void setUnitCompensatePrice(int _unitCompensatePrice);
    void setUnitDelayCost(int _unitDelayCost);
    void setUnitRCancelCost(int _unitRCancelCost);
    void setUnitTimeDelayCost(int _unitTimeDelayCost);

protected:
    BSConfig();
    static BSConfig* _instance;
private:
    bool init();
    QMap<QString, QString> confMap;


    int unitRPrice;
    int unitCompensatePrice;
    int unitDelayCost;
    int unitRCancelCost;
    int unitTimeDelayCost;
};

#endif // BSCONFIG_H
