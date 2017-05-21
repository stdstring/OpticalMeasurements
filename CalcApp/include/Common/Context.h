#pragma once

#include <QHash>
#include <QObject>
#include <QString>
#include <QStringList>

#include "CommonDefs.h"

namespace CalcApp
{

class IContextItem : public QObject
{
    Q_OBJECT
public:
    explicit IContextItem(QObject *parent = nullptr);
    virtual ~IContextItem() {}

signals:
    void DataChanged();
};

// TODO (std_string) : probably we need some encapsulation here
class QStringListContextItem : public IContextItem
{
public:
    QStringList Data;
};

class Context : public QObject
{
    Q_OBJECT
public:
    explicit Context(QObject *parent = nullptr);
    bool HasKey(QString const &key) const;
    ContextItemPtr Get(QString const &key) const;
    void Set(QString const &key, ContextItemPtr item);
    void Clear();

    template <typename TResult> TResult* GetValue(QString const &key) const
    {
        return dynamic_cast<TResult*>(Get(key).get());
    }

private:
    QHash<QString, ContextItemPtr> _storage;

signals:
    void DataChanged(QString const &key);
    void DataCompleted(QString const &key);
};

}

