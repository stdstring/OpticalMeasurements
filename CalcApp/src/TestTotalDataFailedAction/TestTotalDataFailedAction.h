#pragma once

#include <QObject>
#include <QString>

#include "Common/CommonDefs.h"
#include "Common/IAction.h"

namespace CalcApp
{

class TestTotalDataFailedAction : public IAction
{
public:
    TestTotalDataFailedAction(QString const &name, QString const &sourceKey, QString const &destKey, int failedIteration, ContextPtr context, ExecutionStatePtr state);

    virtual QString GetName() override;
    //virtual void StartAction(Context &context) override;
    //virtual void Run(Context &context) override;

protected:
    virtual void ProcessStartImpl() override;
    virtual void ProcessStopImpl() override;
    virtual void CleanupNonFinished() override;

private:
    void ProcessTotalData();

private:
    QString _name;
    QString _sourceKey;
    QString _destKey;
    int _failedIteration;
};

}
