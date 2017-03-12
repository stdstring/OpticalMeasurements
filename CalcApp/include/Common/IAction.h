#pragma once

#include <QObject>
#include <QString>
#include <QtPlugin>

#include "IComponentInfo.h"
#include "Context.h"
#include "MainConfig.h"

namespace CalcApp
{

class IAction : public QObject
{
    Q_OBJECT
public:
    explicit IAction(QObject *parent = nullptr) : QObject(parent) {}

    virtual QString GetName() = 0;
    virtual void StartAction(Context &context) = 0;

signals:
    void ActionFinished();
};

class IActionFactory : public IComponentInfo
{
public:
    virtual IAction* Create(QString const &name, MainConfig const &config, QObject *parent) = 0;
    virtual ComponentType GetComponentType() override { return ComponentType::ACTION; }
};

}

Q_DECLARE_INTERFACE(CalcApp::IActionFactory, "com.stdstring.CalcApp.IActionFactory")
