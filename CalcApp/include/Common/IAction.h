#pragma once

#include <QObject>
#include <QString>

#include <memory>

#include "Context.h"
#include "ExceptionData.h"

namespace CalcApp
{

class IAction : public QObject
{
    Q_OBJECT
public:
    explicit IAction(std::shared_ptr<Context> context) : QObject(), _context(context)
    {
    }

    virtual QString GetName() = 0;
    //virtual void Run(Context &context) = 0;
    //virtual void StartAction(Context &context) = 0;

protected:
    virtual void ProcessStartImpl() = 0;
    virtual void ProcessStopImpl() = 0;
    std::shared_ptr<Context> GetContext() const { return _context; }

private:
    std::shared_ptr<Context> _context;

signals:
    void DataCompleted(QString const &key);
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
