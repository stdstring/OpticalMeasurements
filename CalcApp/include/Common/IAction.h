#pragma once

#include <QObject>
#include <QString>

#include <exception>
#include <memory>

#include "Context.h"

namespace CalcApp
{

class IAction : public QObject
{
    Q_OBJECT
public:
    explicit IAction(std::shared_ptr<Context> context/*, QObject *parent = nullptr*/) : QObject(/*parent*/)
    {
        Q_UNUSED(context)
    }

    virtual QString GetName() = 0;
    /*virtual void Run(Context &context) = 0;*/
    /*virtual void StartAction(Context &context) = 0;*/

protected:
    virtual void ProcessStartImpl() = 0;
    virtual void ProcessStopImpl() = 0;

signals:
    void DataCompleted(QString const &key);
    void ErrorOccured(std::exception_ptr exception);
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

/*void IAction::ProcessStart()
{
    ProcessStartImpl();
}

void IAction::ProcessStop()
{
    ProcessStopImpl();
}*/

}
