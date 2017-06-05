#pragma once

#include <QMultiMap>
#include <QObject>
#include <QString>
#include <QtPlugin>

#include "Common/IActionFactory.h"

namespace CalcApp
{

class TestPartDataConsumerActionFactory : public IActionFactory
{
    Q_OBJECT
    Q_INTERFACES(CalcApp::IActionFactory)
    Q_PLUGIN_METADATA(IID "com.stdstring.CalcApp.IActionFactory" FILE "TestPartDataConsumerAction.json")
public:
    explicit TestPartDataConsumerActionFactory(QObject *parent = nullptr);

    virtual QString GetType() override;
    virtual ActionPtr Create(QString const &name, QMultiMap<QString, QString> const &args, ServiceLocatorPtr serviceLocator, ContextPtr context) override;
};

}
