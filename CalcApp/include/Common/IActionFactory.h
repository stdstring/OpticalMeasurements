#pragma once

#include <QObject>
#include <QString>
#include <QtPlugin>

#include "IAction.h"
#include "IComponentInfo.h"
#include "MainConfig.h"

namespace CalcApp
{

class IActionFactory : public IComponentInfo
{
public:
    explicit IActionFactory(QObject *parent = nullptr) : IComponentInfo(parent) {}

    virtual IAction* Create(QString const &name, QString const &args, MainConfig const &config, QObject *parent) = 0;
    virtual ComponentType GetComponentType() override { return ComponentType::ACTION; }
};

}

Q_DECLARE_INTERFACE(CalcApp::IActionFactory, "com.stdstring.CalcApp.IActionFactory")

