#pragma once

#include <QObject>
#include <QString>
#include <QtPlugin>

#include "Common/CommonDefs.h"
#include "Common/IActionFactory.h"

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
    virtual ActionPtr Create(QString const &name, QString const &args, ServiceLocatorPtr serviceLocator, ContextPtr context) override;
};

}
