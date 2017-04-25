#pragma once

#include <QHash>
#include <QObject>
#include <QString>
#include <QStringList>

#include <memory>

namespace CalcApp
{

class IContextItem
{
public:
    virtual ~IContextItem() {}
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
    std::shared_ptr<IContextItem> Get(QString const &key) const;
    void Set(QString const &key, std::shared_ptr<IContextItem> item);
    void Clear();

    template <typename TResult> TResult* GetValue(QString const &key) const
    {
        return dynamic_cast<TResult*>(Get(key).get());
    }

private:
    QHash<QString, std::shared_ptr<IContextItem>> _storage;

signals:
    void DataChanged(QString const &key);
    void DataCompleted(QString const &key);
};

}

