#pragma once

#include <QObject>
#include <QString>
#include <QtPlugin>

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
    virtual IAction* Create(QString const &name, QString const &args, ServiceLocator const & serviceLocator, QObject *parent) override;
};

}
