#pragma once

#include <QObject>
#include <QString>

#include "Common/CommonDefs.h"
#include "Common/IAction.h"

namespace CalcApp
{

class TestTotalDataConsumerAction : public IAction
{
public:
    explicit TestTotalDataConsumerAction(QString const &name, ContextPtr context);

    virtual QString GetName() override;
    //virtual void StartAction(Context &context) override;
    //virtual void Run(Context &context) override;

protected:
    virtual void ProcessStartImpl() override;
    virtual void ProcessStopImpl() override;

private:
    void GenerateNextItem();

private:
    QString _name;
};

}
