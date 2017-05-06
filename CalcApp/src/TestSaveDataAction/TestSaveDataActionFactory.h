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

class TestSaveDataActionFactory : public IActionFactory
{
    Q_OBJECT
    Q_INTERFACES(CalcApp::IActionFactory)
    Q_PLUGIN_METADATA(IID "com.stdstring.CalcApp.IActionFactory" FILE "TestSaveDataAction.json")
public:
    explicit TestSaveDataActionFactory(QObject *parent = nullptr);

    virtual QString GetId() override;
    virtual std::shared_ptr<IAction> Create(QString const &name, QString const &args, ServiceLocator const &serviceLocator, std::shared_ptr<Context> context) override;
};

}
