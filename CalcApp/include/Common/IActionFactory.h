#pragma once

#include <QObject>
#include <QString>
#include <QtPlugin>

#include <memory>

#include "Context.h"
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

    virtual std::shared_ptr<IAction> Create(QString const &name, QString const &args, ServiceLocator const &serviceLocator, std::shared_ptr<Context> context) = 0;
    virtual ComponentType GetComponentType() override { return ComponentType::ACTION; }
};

}

Q_DECLARE_INTERFACE(CalcApp::IActionFactory, "com.stdstring.CalcApp.IActionFactory")
