#pragma once

#include <QObject>
#include <QString>
#include <QtPlugin>

#include "Common/IActionFactory.h"

namespace CalcApp
{

class TestDataGeneratorActionFactory : public IActionFactory
{
    Q_OBJECT
    Q_INTERFACES(CalcApp::IActionFactory)
    Q_PLUGIN_METADATA(IID "com.stdstring.CalcApp.IActionFactory" FILE "TestDataGeneratorAction.json")
public:
    explicit TestDataGeneratorActionFactory(QObject *parent = nullptr);

    virtual QString GetType() override;
    virtual ActionPtr Create(QString const &name, QString const &args, ServiceLocatorPtr serviceLocator, ContextPtr context) override;
};

}
