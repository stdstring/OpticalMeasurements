#pragma once

#include <QList>
#include <QString>

#include "IActionFactory.h"
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
    IActionFactory* FindAction(QString const &id) const;
    ITransportFactory* GetTransport() const;

    ComponentStorage(ComponentStorage const&) = delete;
    ComponentStorage(ComponentStorage&&) = delete;
    ComponentStorage& operator=(ComponentStorage const&) = delete;
    ComponentStorage& operator=(ComponentStorage&&) = delete;

private:
    void AddAction(IActionFactory *action);
    void SetTransport(ITransportFactory *transport);

    QList<IActionFactory*> _actions;
    ITransportFactory *_transport;
};

}
