#include <QString>

#include <memory>
#include <stdexcept>

#include "Context.h"

namespace CalcApp
{

IContextItem::IContextItem(QObject *parent) : QObject(parent)
{
}

Context::Context(QObject *parent) : QObject(parent)
{
}

bool Context::HasKey(QString const &key) const
{
    return _storage.find(key) != _storage.cend();
}

std::shared_ptr<IContextItem> Context::Get(QString const &key) const
{
    QHash<QString, std::shared_ptr<IContextItem>>::const_iterator iterator = _storage.find(key);
    if (_storage.cend() == iterator)
        throw std::invalid_argument("key");
    return iterator.value();
}

void Context::Set(QString const &key, std::shared_ptr<IContextItem> item)
{
    _storage.insert(key, item);
    QObject::connect(item.get(), &IContextItem::DataChanged, this, [key, this](){ emit this->DataChanged(key); });
}

void Context::Clear()
{
    _storage.clear();
}

}
