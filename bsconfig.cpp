#include "bsconfig.h"

#include <QFile>
#include <QDebug>
#include <QTextCodec>
#include <QList>
#include <QStringList>

BSConfig* BSConfig::_instance = 0;

const QString conf_filename  = "bs_reward.conf";

BSConfig* BSConfig::Instance()
{
    if( 0 == _instance)
    {
        _instance =  new BSConfig();
    }
    return _instance;
}

BSConfig::BSConfig()
{
    unitRPrice = -1;
    unitCompensatePrice = -1;
    unitDelayCost = -1;
    unitRCancelCost = -1;
    unitTimeDelayCost = -1;
    init();
}

bool BSConfig::init()
{
    QFile file(conf_filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "Can not open conf_filename: " << conf_filename;
        return false;
    }
    QTextStream floStream(&file);
    QString line;
    QTextCodec *codec=QTextCodec::codecForName("GBK");
    floStream.setCodec(codec);
    while (!floStream.atEnd())
    {
        line = codec->fromUnicode(floStream.readLine());
        QStringList list = line.split("=");
        if (list.size() != 2) {
            continue;
        }
        confMap[list[0]] = list[1];
    }
    file.close();

    qDebug() << "BSConfig::init() finished.";
    return true;
}

int BSConfig::getUnitRPrice()
{
    if (unitRPrice == -1)
        unitRPrice = confMap["UnitRPrice"].toInt();
    return unitRPrice;
}

int BSConfig::getUnitCompensatePrice()
{
    if (unitCompensatePrice == -1)
        unitCompensatePrice = confMap["UnitCompensatePrice"].toInt();
    return unitCompensatePrice;
}

int BSConfig::getUnitDelayCost()
{
    if (unitDelayCost == -1)
        unitDelayCost = confMap["UnitDelayCost"].toInt();
    return unitDelayCost;
}

int BSConfig::getUnitRCancelCost()
{
    if (unitRCancelCost == -1)
        unitRCancelCost = confMap["UnitRCancelCost"].toInt();
    return unitRCancelCost;
}

int BSConfig::getUnitTimeDelayCost()
{
    if (unitTimeDelayCost == -1)
        unitTimeDelayCost = confMap["UnitTimeDelayCost"].toInt();
    return unitTimeDelayCost;
}

void BSConfig::setUnitRPrice(int _unitRPrice)
{
    unitRPrice = _unitRPrice;
}

void BSConfig::setUnitCompensatePrice(int _unitCompensatePrice)
{
    unitCompensatePrice = _unitCompensatePrice;
}

void BSConfig::setUnitDelayCost(int _unitDelayCost)
{
    unitDelayCost = _unitDelayCost;
}

void BSConfig::setUnitRCancelCost(int _unitRCancelCost)
{
    unitRCancelCost = _unitRCancelCost;
}

void BSConfig::setUnitTimeDelayCost(int _unitTimeDelayCost)
{
    unitTimeDelayCost = _unitTimeDelayCost;
}
