#pragma once

#include <QHash>
#include <QList>
#include <QObject>
#include <QReadWriteLock>
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
    void NotifyDataChange();
    virtual ~IContextItem();

    // TODO (std_string) : probably we need some encapsulation here
    QReadWriteLock Lock;

signals:
    void DataChanged();
};

// TODO (std_string) : probably we need some encapsulation here
class QStringListContextItem : public IContextItem
{
public:
    QStringList Data;
};

// TODO (std_string) : probably we need some encapsulation here
template <typename TItem> class QListContextItem : public IContextItem
{
public:
    QList<TItem> Data;
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
    mutable QReadWriteLock _lock;

signals:
    void DataChanged(QString key);
    void DataCompleted(QString key);
};

}

