#pragma once

#include <QList>

#include "IAction.h"
#include "IComponentInfo.h"
#include "ITransportFactory.h"

namespace CalcApp
{

class ComponentStorage
{
public:
    ComponentStorage();
    void AddComponent(IComponentInfo *component);
    void AddComponents(QList<IComponentInfo*> components);

    ComponentStorage(ComponentStorage const&) = delete;
    ComponentStorage(ComponentStorage&&) = delete;
    ComponentStorage& operator=(ComponentStorage const&) = delete;
    ComponentStorage& operator=(ComponentStorage&&) = delete;

private:
    QList<IActionFactory*> _actions;
    ITransportFactory *_transport;
};

}
