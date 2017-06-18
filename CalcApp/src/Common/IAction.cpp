#include <QObject>

#include "CommonDefs.h"
#include "Context.h"
#include "ExecutionState.h"
#include "IAction.h"

namespace CalcApp
{

IAction::IAction(ContextPtr context, ExecutionStatePtr state) :
    QObject(),
    _context(context),
    _state(state),
    _isActionFinished(false)
{
    QObject::connect(this, &IAction::ActionFinished, this, [this](){ _isActionFinished = true; });
}

ContextPtr IAction::GetContext() const
{
    return _context;
}

ExecutionStatePtr IAction::GetExecutionState() const
{
    return _state;
}

void IAction::ProcessStart()
{
    ProcessStartImpl();
}

void IAction::ProcessStop()
{
    if (!_isActionFinished)
        CleanupNonFinished();
    ProcessStopImpl();
}

}
