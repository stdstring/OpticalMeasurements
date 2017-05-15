#pragma once

#include <QObject>
#include <QString>

#include <exception>
#include <memory>

#include "Context.h"

namespace CalcApp
{

class ExceptionData
{
public:
    ExceptionData() {}
    explicit ExceptionData(std::exception_ptr exception) : Exception(exception) {}

    std::exception_ptr Exception;
};

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
    //void ErrorOccured(std::exception_ptr exception);
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

Q_DECLARE_METATYPE(CalcApp::ExceptionData);
