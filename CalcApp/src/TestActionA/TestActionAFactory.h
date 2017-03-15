#pragma once

#include <QObject>
#include <QString>

#include "Common/IActionFactory.h"
#include "Common/MainConfig.h"

namespace CalcApp
{

class TestActionAFactory : IActionFactory
{
    Q_OBJECT
public:
    explicit TestActionAFactory(QObject *parent = nullptr);

    virtual QString GetId() override;
    virtual IAction* Create(QString const &name, QString const &args, MainConfig const &config, QObject *parent) override;
};

}