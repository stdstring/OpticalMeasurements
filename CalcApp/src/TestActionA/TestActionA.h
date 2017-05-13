#pragma once

#include <QObject>
#include <QString>

#include <memory>

#include "Common/Context.h"
#include "Common/IAction.h"

namespace CalcApp
{

class TestActionA : public IAction
{
public:
    explicit TestActionA(QString const &name, int time, std::shared_ptr<Context> context);

    virtual QString GetName() override;
    //virtual void StartAction(Context &context) override;
    //virtual void Run(Context &context) override;

protected:
    virtual void ProcessStartImpl() override;
    virtual void ProcessStopImpl() override;

private:
    QString _name;
    int _time;
};

}
