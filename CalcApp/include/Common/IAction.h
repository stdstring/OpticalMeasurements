#pragma once

#include <QObject>
#include <QString>

#include "CommonDefs.h"
#include "ExceptionData.h"

namespace CalcApp
{

class IAction : public QObject
{
    Q_OBJECT
public:
    explicit IAction(ContextPtr context, ExecutionStatePtr state);

    virtual QString GetName() = 0;
    //virtual void Run(Context &context) = 0;
    //virtual void StartAction(Context &context) = 0;

protected:
    virtual void ProcessStartImpl() = 0;
    virtual void ProcessStopImpl() = 0;
    virtual void CleanupNonFinished() = 0;
    ContextPtr GetContext() const;
    ExecutionStatePtr GetExecutionState() const;

private:
    ContextPtr _context;
    ExecutionStatePtr _state;
    bool _isActionFinished;

signals:
    void ErrorOccured(ExceptionData exception);
    void ActionFinished();

public slots:
    void ProcessStart();
    void ProcessStop();
};

}
