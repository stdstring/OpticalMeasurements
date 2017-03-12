#pragma once

#include <QList>
#include <QString>

namespace CalcApp
{

struct ActionDef
{
public:
    ActionDef(QString const &id, QString const &name, QString const &argsString) :
        Id(id),
        Name(name),
        ArgsString(argsString)
    {
    }

    QString Id;
    QString Name;
    QString ArgsString;
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
