#include <QObject>
#include <QString>

#include "Common/CommonDefs.h"
#include "Common/Context.h"
#include "Common/IAction.h"
#include "DataReceiverAction.h"

namespace CalcApp
{

DataReceiverAction::DataReceiverAction(QString const &name, QString const &key, ContextPtr context, ExecutionStatePtr state) :
    IAction(context, state),
    _name(name),
    _key(key)
{
}

QString DataReceiverAction::GetName()
{
    return _name;
}

/*void DataReceiverAction::StartAction(Context &context)
{
}*/

/*void DataReceiverAction::Run(Context &context)
{
}*/

void DataReceiverAction::ProcessStartImpl()
{
}

void DataReceiverAction::ProcessStopImpl()
{
}

void DataReceiverAction::CleanupNonFinished()
{
}

}
