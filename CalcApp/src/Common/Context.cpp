#include <QReadLocker>
#include <QReadWriteLock>
#include <QString>
#include <QWriteLocker>

#include <stdexcept>

#include "CommonDefs.h"
#include "Context.h"

namespace CalcApp
{

IContextItem::IContextItem(QObject *parent) : QObject(parent), Lock(QReadWriteLock::NonRecursive)
{
}

void IContextItem::NotifyDataChange()
{
    emit DataChanged();
}

IContextItem::~IContextItem()
{
    // do nothing
}

Context::Context(QObject *parent) : QObject(parent), _lock(QReadWriteLock::NonRecursive)
{
}

bool Context::HasKey(QString const &key) const
{
    return _storage.find(key) != _storage.cend();
}

ContextItemPtr Context::Get(QString const &key) const
{
    QReadLocker locker(&_lock);
    QHash<QString, ContextItemPtr>::const_iterator iterator = _storage.find(key);
    if (_storage.cend() == iterator)
        throw std::invalid_argument("key");
    return iterator.value();
}

void Context::Set(QString const &key, ContextItemPtr item)
{
    QWriteLocker locker(&_lock);
    _storage.insert(key, item);
    QObject::connect(item.get(), &IContextItem::DataChanged, this, [key, this](){ emit this->DataChanged(key); });
}

void Context::Clear()
{
    _storage.clear();
}

}
