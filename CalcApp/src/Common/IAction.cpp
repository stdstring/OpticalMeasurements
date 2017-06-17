#include <QObject>

#include "CommonDefs.h"
#include "Context.h"
#include "IAction.h"

namespace CalcApp
{

IAction::IAction(ContextPtr context) :
    QObject(),
    _context(context),
    _isActionFinished(false)
{
    QObject::connect(this, &IAction::ActionFinished, this, [this](){ _isActionFinished = true; });
}

ContextPtr IAction::GetContext() const
{
    return _context;
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
