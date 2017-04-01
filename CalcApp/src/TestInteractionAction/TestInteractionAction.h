#pragma once

#include <QObject>
#include <QString>

#include "Common/Context.h"
#include "Common/IAction.h"

namespace CalcApp
{

class TestInteractionAction : public IAction
{
public:
    explicit TestInteractionAction(QString const &name, QObject *parent = nullptr);

    virtual QString GetName() override;
    /*virtual void StartAction(Context &context) override;*/
    virtual void Run(Context &context) override;

private:
    QString _name;
};

}
