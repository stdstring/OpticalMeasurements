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

struct ActionChainDef
{
public:
    ActionChainDef(QString const &name, QList<ActionDef> const &actions) :
        Name(name),
        Actions(actions)
    {
    }

    QString Name;
    QList<ActionDef> Actions;
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
