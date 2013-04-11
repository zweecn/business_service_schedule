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
    return confMap["UnitRPrice"].toInt();
}

int BSConfig::getUnitCompensatePrice()
{
    return confMap["UnitCompensatePrice"].toInt();
}

int BSConfig::getUnitDelayCost()
{
    return confMap["UnitDelayCost"].toInt();
}

int BSConfig::getUnitRCancelCost()
{
    return confMap["UnitRCancelCost"].toInt();
}

int BSConfig::getUnitTimeDelayCost()
{
    return confMap["UnitTimeDelayCost"].toInt();
}
