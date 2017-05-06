#pragma once

#include <QObject>
#include <QString>
#include <QtPlugin>

#include <memory>

#include "Common/Context.h"
#include "Common/IActionFactory.h"
#include "Common/ServiceLocator.h"

namespace CalcApp
{

class TestActionAFactory : public IActionFactory
{
    Q_OBJECT
    Q_INTERFACES(CalcApp::IActionFactory)
    Q_PLUGIN_METADATA(IID "com.stdstring.CalcApp.IActionFactory" FILE "TestActionA.json")
public:
    explicit TestActionAFactory(QObject *parent = nullptr);

    virtual QString GetId() override;
    virtual std::shared_ptr<IAction> Create(QString const &name, QString const &args, ServiceLocator const &serviceLocator, std::shared_ptr<Context> context) override;
};

}
