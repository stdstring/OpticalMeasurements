#include <QList>
#include <QObject>

#include <algorithm>

#include "ComponentStorage.h"
#include "IAction.h"
#include "IComponentInfo.h"
#include "ITransportFactory.h"

namespace CalcApp
{

ComponentStorage::ComponentStorage() :
    _transport(nullptr)
{
}

void ComponentStorage::AddComponent(IComponentInfo *component)
{
    switch (component->GetComponentType())
    {
        case ComponentType::ACTION:
        {
            IActionFactory *action = qobject_cast<IActionFactory*>(component);
            _actions.append(action);
            break;
        }
        case ComponentType::TRANSPORT:
        {
            // TODO (std_string) : think about processing of situation with several transport's module
            delete _transport;
            _transport = qobject_cast<ITransportFactory*>(component);
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

}
