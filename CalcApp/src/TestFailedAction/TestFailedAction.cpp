#include <QObject>
#include <QString>
#include <QTimer>

#include <exception>
#include <stdexcept>

#include "Common/CommonDefs.h"
#include "Common/Context.h"
#include "Common/IAction.h"
#include "TestFailedAction.h"

namespace CalcApp
{

TestFailedAction::TestFailedAction(const QString &name, int time, ContextPtr context) :
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
}*/

/*void TestFailedAction::Run(Context &context)
{
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

