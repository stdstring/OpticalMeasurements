#include <QObject>
#include <QString>
#include <QTimer>

#include "Common/CommonDefs.h"
#include "Common/Context.h"
#include "Common/IAction.h"
#include "TestActionA.h"

namespace CalcApp
{

TestActionA::TestActionA(QString const &name, int time, ContextPtr context) :
    IAction(context),
    _name(name),
    _time(time)
{
}

QString TestActionA::GetName()
{
    return _name;
}

/*void TestActionA::StartAction(Context &context)
{
}*/

/*void TestActionA::Run(Context &context)
{
}*/

void TestActionA::ProcessStartImpl()
{
    QTimer::singleShot(_time, this, [this](){ emit ActionFinished(); });
}

void TestActionA::ProcessStopImpl()
{
    // do nothing
}

}

