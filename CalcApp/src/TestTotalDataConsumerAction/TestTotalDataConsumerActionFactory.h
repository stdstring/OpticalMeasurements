#pragma once

#include <QObject>
#include <QString>
#include <QtPlugin>

#include "Common/IActionFactory.h"

namespace CalcApp
{

class TestTotalDataConsumerActionFactory : public IActionFactory
{
    Q_OBJECT
    Q_INTERFACES(CalcApp::IActionFactory)
    Q_PLUGIN_METADATA(IID "com.stdstring.CalcApp.IActionFactory" FILE "TestTotalDataConsumerAction.json")
public:
    explicit TestTotalDataConsumerActionFactory(QObject *parent = nullptr);

    virtual QString GetId() override;
    virtual ActionPtr Create(QString const &name, QString const &args, ServiceLocatorPtr serviceLocator, ContextPtr context) override;
};

}
