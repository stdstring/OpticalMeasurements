#pragma once

#include <QObject>
#include <QString>
#include <QtPlugin>

#include "IComponentInfo.h"
#include "MainConfig.h"

namespace CalcApp
{

class IAction
{
public:
    virtual QString GetName() = 0;
    virtual void Process() = 0;
};

class IActionFactory : public IComponentInfo
{
public:
    virtual IAction* Create(MainConfig const &config, QObject *parent) = 0;
    virtual ComponentType GetComponentType() override { return ComponentType::ACTION; }
};

}

Q_DECLARE_INTERFACE(CalcApp::IActionFactory, "com.stdstring.CalcApp.IActionFactory")
