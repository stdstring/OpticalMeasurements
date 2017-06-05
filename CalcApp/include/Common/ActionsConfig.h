#pragma once

#include <QList>
#include <QMultiMap>
#include <QPair>
#include <QString>

namespace CalcApp
{

/*struct ArgumentDef
{
public:
    ArgumentDef(QString const &name, QString const &value) :
        Name(name),
        Value(value)
    {
    }

    QString Name;
    QString Value;
};

struct ActionDef
{
public:
    ActionDef(QString const &name, QString const &type, QList<ArgumentDef> const &args) :
        Name(name),
        Type(type),
        Args(args)
    {
    }

    QString Name;
    QString Type;
    QList<ArgumentDef> Args;
};*/

/*typedef QPair<QString, QString> ArgumentDef;

struct ActionDef
{
public:
    ActionDef(QString const &name, QString const &type, QList<ArgumentDef> const &args) :
        Name(name),
        Type(type),
        Args(args)
    {
    }

    QString Name;
    QString Type;
    QList<ArgumentDef> Args;
};*/

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
