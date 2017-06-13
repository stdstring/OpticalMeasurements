#pragma once

#include <QObject>
#include <QString>

#include "CommonDefs.h"
#include "Context.h"
#include "ExceptionData.h"

namespace CalcApp
{

class IAction : public QObject
{
    Q_OBJECT
public:
    explicit IAction(ContextPtr context) : QObject(), _context(context)
    {
    }

    virtual QString GetName() = 0;
    //virtual void Run(Context &context) = 0;
    //virtual void StartAction(Context &context) = 0;
    virtual void CleanupAtFailure() = 0;

protected:
    virtual void ProcessStartImpl() = 0;
    virtual void ProcessStopImpl() = 0;
    ContextPtr GetContext() const { return _context; }

private:
    ContextPtr _context;

signals:
    void ErrorOccured(ExceptionData exception);
    void ActionFinished();

public slots:
    void ProcessStart()
    {
        ProcessStartImpl();
    }

    void ProcessStop()
    {
        ProcessStopImpl();
    }
};

}
