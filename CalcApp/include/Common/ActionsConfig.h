#pragma once

#include <QList>
#include <QMultiMap>
#include <QPair>
#include <QString>

namespace CalcApp
{

struct ActionDef
{
public:
    ActionDef(QString const &name, QString const &type, QMultiMap<QString, QString> const &args) :
        Name(name),
        Type(type),
        Args(args)
    {
    }

    QString Name;
    QString Type;
    QMultiMap<QString, QString> Args;
};

struct ResultDef
{
public:
    ResultDef(QString const &dataFilename, QString const &viewerName, QString const &descriptor) :
        DataFilename(dataFilename),
        ViewerName(viewerName),
        Descriptor(descriptor)
    {
    }

    QString DataFilename;
    QString ViewerName;
    QString Descriptor;
};

struct ActionChainDef
{
public:
    ActionChainDef(QString const &name, QList<ActionDef> const &actions, QList<ResultDef> const &results) :
        Name(name),
        Actions(actions),
        Results(results)
    {
    }

    QString Name;
    QList<ActionDef> Actions;
    QList<ResultDef> Results;
};

struct ActionsConfig
{
public:
    explicit ActionsConfig(QList<ActionChainDef> const &chains) :
        Chains(chains)
    {
    }

    QList<ActionChainDef> Chains;
};

}
