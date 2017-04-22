#include <QList>
#include <QObject>

#include <algorithm>

#include "IAction.h"
#include "IComponentInfo.h"
#include "ITransportFactory.h"
#include "ComponentStorage.h"

namespace CalcApp
{

ComponentStorage::ComponentStorage() :
    _transport(nullptr)
{
}

void ComponentStorage::AddComponent(IComponentInfo *component)
{
    // TODO (std_string) : use more functional style
    switch (component->GetComponentType())
    {
        case ComponentType::ACTION:
        {
            AddAction(qobject_cast<IActionFactory*>(component));
            break;
        }
        case ComponentType::TRANSPORT:
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

IActionFactory* ComponentStorage::FindAction(QString const &id) const
{
    QList<IActionFactory*>::const_iterator iterator = std::find_if(_actions.cbegin(),
                                                                   _actions.cend(),
                                                                   [&id](IActionFactory* factory){ return factory->GetId() == id; });
    return iterator == _actions.cend() ? nullptr : *iterator;
}

ITransportFactory* ComponentStorage::GetTransport() const
{
    return _transport;
}

void ComponentStorage::AddAction(IActionFactory *action)
{
    // TODO (std_string) : think about processing of situation with several actions modules with the same id
    if (FindAction(action->GetId()) == nullptr)
        _actions.append(action);
    else
        delete action;
}

void ComponentStorage::SetTransport(ITransportFactory *transport)
{
    // TODO (std_string) : think about processing of situation with several transport's module
    if (_transport == nullptr)
        _transport = transport;
    else
        delete transport;
}

}
