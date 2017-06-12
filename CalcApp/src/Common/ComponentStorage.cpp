#include <QList>
#include <QObject>

#include <algorithm>

#include "IActionFactory.h"
#include "IComponentInfo.h"
#include "ITransportFactory.h"
#include "ComponentStorage.h"
#include "TransportServiceFactory.h"

namespace CalcApp
{

ComponentStorage::ComponentStorage() :
    _transport(nullptr)
{
}

void ComponentStorage::AddComponent(IComponentInfo *component)
{
    // TODO (std_string) : use more functional style
    switch (component->GetComponentCategory())
    {
        case ComponentCategory::ACTION:
        {
            AddAction(qobject_cast<IActionFactory*>(component));
            break;
        }
        case ComponentCategory::TRANSPORT:
        {
            SetTransport(qobject_cast<ITransportFactory*>(component));
            break;
        }
        default:
            // TODO (std_string) : think about processing of this situation
            break;
    }
}

void ComponentStorage::AddComponents(QList<IComponentInfo*> components)
{
    foreach(IComponentInfo *component, components)
    {
        AddComponent(component);
    }
}

IActionFactory* ComponentStorage::FindAction(QString const &type) const
{
    QList<IActionFactory*>::const_iterator iterator = std::find_if(_actions.cbegin(),
                                                                   _actions.cend(),
                                                                   [&type](IActionFactory* factory){ return factory->GetType() == type; });
    return iterator == _actions.cend() ? nullptr : *iterator;
}

ITransportFactory* ComponentStorage::GetTransport() const
{
    return _transport;
}

void ComponentStorage::AddAction(IActionFactory *action)
{
    // TODO (std_string) : think about processing of situation with several actions modules with the same id
    if (FindAction(action->GetType()) == nullptr)
        _actions.append(action);
    else
        delete action;
}

void ComponentStorage::SetTransport(ITransportFactory *transport)
{
    // TODO (std_string) : think about processing of situation with several transport's module
    if (_transport == nullptr)
    {
        // TODO (std_string) : create more reliable solution (probably, with help of smart pointers)
        // TODO (std_string) : think about parent of transport
        _transport = new TransportServiceFactory(transport, transport->parent());
    }
    else
        delete transport;
}

}
