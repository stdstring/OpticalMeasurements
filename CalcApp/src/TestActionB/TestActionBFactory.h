#pragma once

#include <QObject>
#include <QString>
#include <QtPlugin>

#include "Common/IActionFactory.h"
#include "Common/ServiceLocator.h"

namespace CalcApp
{

class TestActionBFactory : public IActionFactory
{
    Q_OBJECT
    Q_INTERFACES(CalcApp::IActionFactory)
    Q_PLUGIN_METADATA(IID "com.stdstring.CalcApp.IActionFactory" FILE "TestActionB.json")
public:
    explicit TestActionBFactory(QObject *parent = nullptr);

    virtual QString GetId() override;
    virtual IAction* Create(QString const &name, QString const &args, ServiceLocator const & serviceLocator, QObject *parent) override;
};

}
