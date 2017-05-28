#include <QString>

#include "Common/CommonDefs.h"
#include "Common/Context.h"
#include "Common/IAction.h"
#include "TestTotalDataConsumerAction.h"

namespace CalcApp
{

TestTotalDataConsumerAction::TestTotalDataConsumerAction(QString const &name, ContextPtr context) :
    IAction(context),
    _name(name)
{
}

QString TestTotalDataConsumerAction::GetName()
{
    return _name;
}

/*void TestTotalDataConsumerAction::StartAction(Context &context)
{
}*/

/*void TestTotalDataConsumerAction::Run(Context &context)
{
}*/

void TestTotalDataConsumerAction::ProcessStartImpl()
{
    // do nothing
}

void TestTotalDataConsumerAction::ProcessStopImpl()
{
    // do nothing
}

}
