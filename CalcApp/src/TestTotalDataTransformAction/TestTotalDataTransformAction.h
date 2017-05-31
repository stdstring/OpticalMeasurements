#pragma once

#include <QObject>
#include <QString>

#include "Common/CommonDefs.h"
#include "Common/IAction.h"

namespace CalcApp
{

class TestTotalDataTransformAction : public IAction
{
public:
    TestTotalDataTransformAction(QString const &name, QString const &sourceKey, QString const &destKey, ContextPtr context);

    virtual QString GetName() override;
    //virtual void StartAction(Context &context) override;
    //virtual void Run(Context &context) override;

protected:
    virtual void ProcessStartImpl() override;
    virtual void ProcessStopImpl() override;

private:
    void ProcessTotalData();

private:
    QString _name;
    QString _sourceKey;
    QString _destKey;
};

}