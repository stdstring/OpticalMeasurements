#include <QString>

#include "Common/CommonDefs.h"
#include "Common/Context.h"
#include "Common/ExceptionData.h"
#include "Common/ExecutionState.h"
#include "Common/IAction.h"
#include "CalibrationAction.h"

namespace CalcApp
{

CalibrationAction::CalibrationAction(QString const &name, ContextPtr context, ExecutionStatePtr state) :
    IAction(context, state),
    _name(name)
{
}

QString CalibrationAction::GetName()
{
    return _name;
}

/*void CalibrationAction::StartAction(Context &context)
{
}*/

/*void CalibrationAction::Run(Context &context)
{
}*/

void CalibrationAction::ProcessStartImpl()
{
}

void CalibrationAction::ProcessStopImpl()
{
}

void CalibrationAction::CleanupNonFinished()
{
}

}

