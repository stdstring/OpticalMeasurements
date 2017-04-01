#pragma once

#include <QObject>
#include <QString>
#include <QtPlugin>

#include "Common/IActionFactory.h"
#include "Common/ITransportFactory.h"
#include "Common/MainConfig.h"

namespace CalcApp
{

class TestInteractionActionFactory : public IActionFactory
{
    Q_OBJECT
    Q_INTERFACES(CalcApp::IActionFactory)
    Q_PLUGIN_METADATA(IID "com.stdstring.CalcApp.IActionFactory" FILE "TestInteractionAction.json")
public:
    explicit TestInteractionActionFactory(QObject *parent = nullptr);

    virtual QString GetId() override;
    virtual IAction* Create(QString const &name, QString const &args, MainConfig const &config, ITransportFactory *transportFactory, QObject *parent) override;
};

}
