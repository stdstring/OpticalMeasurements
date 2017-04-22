#pragma once

#include <QObject>
#include <QString>
#include <QtPlugin>

#include "IAction.h"
#include "IComponentInfo.h"
#include "ServiceLocator.h"

namespace CalcApp
{

// TODO (std_string) : think about this definition
class ServiceLocator;

class IActionFactory : public IComponentInfo
{
    Q_OBJECT
public:
    explicit IActionFactory(QObject *parent = nullptr) : IComponentInfo(parent) {}

    // TODO (std_string) : using transportFactory here is temporary solution, only for stage 1. In future, we will create transport per action chain or something similiar.
    virtual IAction* Create(QString const &name, QString const &args, ServiceLocator const &serviceLocator, QObject *parent) = 0;
    virtual ComponentType GetComponentType() override { return ComponentType::ACTION; }
};

}

Q_DECLARE_INTERFACE(CalcApp::IActionFactory, "com.stdstring.CalcApp.IActionFactory")
