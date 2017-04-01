#pragma once

#include <QObject>
#include <QString>
#include <QtPlugin>

#include "Common/IActionFactory.h"
#include "Common/MainConfig.h"

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
    virtual IAction* Create(QString const &name, QString const &args, MainConfig const &config, QObject *parent) override;
};

}
