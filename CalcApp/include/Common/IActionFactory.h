#pragma once

#include <QMultiMap>
#include <QObject>
#include <QString>
#include <QtPlugin>

#include "CommonDefs.h"
#include "IComponentInfo.h"

namespace CalcApp
{

class IActionFactory : public IComponentInfo
{
    Q_OBJECT
public:
    explicit IActionFactory(QObject *parent = nullptr) : IComponentInfo(parent) {}

    virtual ActionPtr Create(QString const &name, QMultiMap<QString, QString> const &args, ServiceLocatorPtr serviceLocator, ContextPtr context) = 0;
    virtual ComponentCategory GetComponentCategory() override { return ComponentCategory::ACTION; }
};

}

Q_DECLARE_INTERFACE(CalcApp::IActionFactory, "com.stdstring.CalcApp.IActionFactory")
