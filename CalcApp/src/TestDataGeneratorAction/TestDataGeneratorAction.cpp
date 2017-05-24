#include <QString>

#include "Common/CommonDefs.h"
#include "Common/Context.h"
#include "Common/IAction.h"
#include "TestDataGeneratorAction.h"

namespace CalcApp
{

TestDataGeneratorAction::TestDataGeneratorAction(const QString &name, ContextPtr context) :
    IAction(context),
    _name(name)
{
}

QString TestDataGeneratorAction::GetName()
{
    return _name;
}

/*void TestDataGeneratorAction::StartAction(Context &context)
{
}*/

/*void TestDataGeneratorAction::Run(Context &context)
{
}*/

void TestDataGeneratorAction::ProcessStartImpl()
{
    // do nothing
}

void TestDataGeneratorAction::ProcessStopImpl()
{
    // do nothing
}

}
