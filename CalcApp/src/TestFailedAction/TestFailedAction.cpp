#include <QObject>
#include <QString>
#include <QTimer>

#include <exception>
#include <memory>
#include <stdexcept>

#include "Common/Context.h"
#include "Common/IAction.h"
#include "TestFailedAction.h"

namespace CalcApp
{

TestFailedAction::TestFailedAction(const QString &name, int time, std::shared_ptr<Context> context) :
    IAction(context),
    _name(name),
    _time(time)
{
}

QString TestFailedAction::GetName()
{
    return _name;
}

/*void TestFailedAction::StartAction(Context &context)
{
    Q_UNUSED(context);
    QTimer::singleShot(_time, this, [this](){ emit ActionFinished(); });
}*/

/*void TestFailedAction::Run(Context &context)
{
    Q_UNUSED(context);
    QThread::msleep(_time);
    throw std::logic_error("Internal error: action is failed");
}*/

void TestFailedAction::ProcessStartImpl()
{
    QTimer::singleShot(_time, this, [this]()
    {
        emit ErrorOccured(ExceptionData(std::make_exception_ptr(std::logic_error("Internal error: action is failed"))));
    });
}

void TestFailedAction::ProcessStopImpl()
{
    // do nothing
}

}

