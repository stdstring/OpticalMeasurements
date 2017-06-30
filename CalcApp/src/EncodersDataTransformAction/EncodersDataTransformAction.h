#pragma once

#include <QObject>
#include <QString>

#include "Common/CommonDefs.h"
#include "Common/IAction.h"

namespace CalcApp
{

class EncodersDataTransformAction : public IAction
{
public:
    EncodersDataTransformAction(QString const &name, QString const &sourceKey, QString const &destKey, ContextPtr context, ExecutionStatePtr state);

    virtual QString GetName() override;
    //virtual void StartAction(Context &context) override;
    //virtual void Run(Context &context) override;

protected:
    virtual void ProcessStartImpl() override;
    virtual void ProcessStopImpl() override;
    virtual void CleanupNonFinished() override;

private:
    void ProcessData();
    void FinishProcessData();
    void ProcessData(ContextPtr context);

private:
    QString _name;
    QString _sourceKey;
    QString _destKey;
    // TODO (std_string) : probably move into separate state object
    int _index;
};

}