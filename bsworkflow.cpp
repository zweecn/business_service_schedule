#include "bsworkflow.h"

#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <QTextCodec>
#include <QStringList>

#include <iostream>

BSWorkFlow* BSWorkFlow::_instance = 0;

const QString bs_snode_filename = "bs_snode.conf";
const QString bs_resoruce_filename = "bs_resource.conf";
const QString bs_requirement_filename = "bs_requirement.conf";
const QString bs_instance_filename = "bs_instance.conf";

BSWorkFlow* BSWorkFlow::Instance()
{
    if( 0 == _instance)
    {
        _instance =  new BSWorkFlow();
    }
    return _instance;
}

BSWorkFlow::BSWorkFlow()
{
    readBSSNodeList();
    readBSResourceList();
    readBSRequirementQueue();
    readBSInstanceList();
}


bool BSWorkFlow::readBSSNodeList()
{
    QFile file(bs_snode_filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qWarning() << "Can not open bs_snode_filename: " << bs_snode_filename;
        return false;
    }
    QTextStream floStream(&file);
    QString line;
    QTextCodec *codec=QTextCodec::codecForName("GBK");
    floStream.setCodec(codec);
    line = codec->fromUnicode(floStream.readLine());
    line = codec->fromUnicode(floStream.readLine());
    nodeSize = line.split("\t")[0].toInt();
    int column_size = line.split("\t")[1].toInt();
    int i = 0;
    while (!floStream.atEnd() && i < nodeSize)
    {
        line = codec->fromUnicode(floStream.readLine());
        QStringList list = line.split("\t");
        if (list.size() != column_size) {
            continue;
        }
        BSSNode node;
        node.sid = list[0].toInt();
        node.resType = list[1].toInt();
        node.unitReqQLevel = list[2].toInt();
        node.concurrencyType = list[3].toInt();
        bsSNodeList.append(node);
        i++;
    }
    file.close();

    if (i != nodeSize)
    {
        qWarning() << "bs_snode_filename:" << bs_snode_filename << "configure error.";
        return false;
    }

    qDebug() << "BSWorkFlow::readBSSNodeList() finised.";
    return true;
}

bool BSWorkFlow::readBSResourceList()
{
    QFile file(bs_resoruce_filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qWarning() << "Can not open bs_resoruce_filename: " << bs_resoruce_filename;
        return false;
    }
    QTextStream floStream(&file);
    QString line;
    QTextCodec *codec=QTextCodec::codecForName("GBK");
    floStream.setCodec(codec);
    line = codec->fromUnicode(floStream.readLine());
    line = codec->fromUnicode(floStream.readLine());
    resourceSize = line.split("\t")[0].toInt();
    int column_size = line.split("\t")[1].toInt();
    int i = 0;
    int peroidSize = 2;
    while (!floStream.atEnd() && i < peroidSize * resourceSize)
    {
        line = codec->fromUnicode(floStream.readLine());
        QStringList list = line.split("\t");
        if (list.size() != column_size) {
            continue;
        }
        BSResource node;
        node.period = list[0].toInt();
        node.resType = list[1].toInt();
        node.totalQLevel = list[2].toInt();
        node.price = list[3].toInt();
        bsResourceList.append(node);
        i++;
    }
    file.close();

    if (i != peroidSize * resourceSize)
    {
        qWarning() << "bs_resoruce_filename:" << bs_resoruce_filename << "configure error.";
        return false;
    }

    qDebug() << "BSWorkFlow::readBSResourceList() finised.";
    return true;
}

bool BSWorkFlow::readBSRequirementQueue()
{
    QFile file(bs_requirement_filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qWarning() << "Can not open bs_requirement_filename: " << bs_requirement_filename;
        return false;
    }
    QTextStream floStream(&file);
    QString line;
    QTextCodec *codec=QTextCodec::codecForName("GBK");
    floStream.setCodec(codec);
    line = codec->fromUnicode(floStream.readLine());
    line = codec->fromUnicode(floStream.readLine());
    requirementSize = line.split("\t")[0].toInt();
    int column_size = line.split("\t")[1].toInt();
    int i = 0;
    while (!floStream.atEnd() && i < requirementSize)
    {
        line = codec->fromUnicode(floStream.readLine());
        QStringList list = line.split("\t");
        if (list.size() != column_size) {
            continue;
        }
        BSRequirement node;
        node.customer = list[0].toInt();
        node.qLevel = list[1].toInt();
        node.expectedPeriod = list[2].toInt();
        node.wtp = list[3].toInt();
        node.setFree(true);
        bsRequirementQueue.append(node);
        i++;
    }
    file.close();

    if (i != requirementSize)
    {
        qWarning() << "bs_requirement_filename:" << bs_requirement_filename << "configure error.";
        return false;
    }

    qDebug() << "BSWorkFlow::readBSResourceList() finised.";
    return true;
}

bool BSWorkFlow::readBSInstanceList()
{
    QFile file(bs_instance_filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qWarning() << "Can not open bs_instance_filename: " << bs_instance_filename;
        return false;
    }
    QTextStream floStream(&file);
    QString line;
    QTextCodec *codec=QTextCodec::codecForName("GBK");
    floStream.setCodec(codec);
    line = codec->fromUnicode(floStream.readLine());
    line = codec->fromUnicode(floStream.readLine());
    instanceSize = line.toInt();

    int i = 0;
    while (!floStream.atEnd() && i < instanceSize)
    {
        line = codec->fromUnicode(floStream.readLine());
        QStringList list = line.split("\t");
        if (list.size() != 2) {
            continue;
        }
        BSInstance node;
        node.instanceID = list[0].toInt();
        node.requirementID = list[1].toInt();
        for (int j = 0; j < bsRequirementQueue.size(); j++)
        {
            if (bsRequirementQueue[j].customer == node.requirementID)
            {
                bsRequirementQueue[j].setFree(false);
                break;
            }
        }
        bsInstanceList.append(node);
        i++;
    }
    if (i != instanceSize)
    {
        qWarning() << "bs_instance_filename:" << bs_instance_filename << "configure error.";
        file.close();
        return false;
    }

    line = codec->fromUnicode(floStream.readLine());
    line = codec->fromUnicode(floStream.readLine());
    nodeSize = line.toInt();
    i = 0;
    while (!floStream.atEnd() && i < nodeSize)
    {
        line = codec->fromUnicode(floStream.readLine());
        QStringList list = line.split("\t");
        if (list.size() != instanceSize+2) {
            continue;
        }
        int sid = list[0].toInt();
        for (int j = 0; j < instanceSize; j++)
        {
            BSSNodePlan node;
            node.snodeID = sid;
            QStringList startEnd = list[2 + j].split("->");
            node.startTime = startEnd[0].toInt();
            node.endTime = startEnd[1].toInt();
            bsInstanceList[j].sNodePlanList.append(node);
        }
        i++;
    }
    file.close();
    if (i != nodeSize)
    {
        qWarning() << "bs_instance_filename:" << bs_instance_filename << "configure error.";
        return false;
    }

    qDebug() << "BSWorkFlow::readBSResourceList() finised.";
    return true;
}

void BSWorkFlow::showInstanceList()
{
    std::cout << "Instance list is:\n";
    for (int i = 0; i < bsInstanceList.size(); i++)
    {
        std::cout << bsInstanceList[i].toString().toStdString() << std::endl;
    }
}

void BSWorkFlow::showRequirementQueue()
{
    std::cout << "Requirement queue is:\n";
    for (int i = 0; i < bsRequirementQueue.size(); i++)
    {
        std::cout << bsRequirementQueue[i].toString().toStdString() << std::endl;
    }
}

void BSWorkFlow::showSNodeList()
{
    std::cout << "SNode list is:\n";
    for (int i = 0; i < bsSNodeList.size(); i++)
    {
        std::cout << bsSNodeList[i].toString().toStdString() << std::endl;
    }
}

void BSWorkFlow::showResourceList()
{
    std::cout << "Resource list is:\n";
    for (int i = 0; i < bsResourceList.size(); i++)
    {
        std::cout << bsResourceList[i].toString().toStdString() << std::endl;
    }
}