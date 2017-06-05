#pragma once

#include <QMultiMap>
#include <QObject>
#include <QString>
#include <QtPlugin>

//#include <memory>

#include "Common/CommonDefs.h"
//#include "Common/Context.h"
#include "Common/IActionFactory.h"
//#include "Common/ServiceLocator.h"

namespace CalcApp
{

class TestSaveDataActionFactory : public IActionFactory
{
    Q_OBJECT
    Q_INTERFACES(CalcApp::IActionFactory)
    Q_PLUGIN_METADATA(IID "com.stdstring.CalcApp.IActionFactory" FILE "TestSaveDataAction.json")
public:
    explicit TestSaveDataActionFactory(QObject *parent = nullptr);

    virtual QString GetType() override;
    virtual ActionPtr Create(QString const &name, QMultiMap<QString, QString> const &args, ServiceLocatorPtr serviceLocator, ContextPtr context) override;
};

}
