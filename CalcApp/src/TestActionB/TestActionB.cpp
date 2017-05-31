#include <QObject>
#include <QString>
#include <QTimer>

#include "Common/CommonDefs.h"
#include "Common/Context.h"
#include "Common/IAction.h"
#include "TestActionB.h"

namespace CalcApp
{

TestActionB::TestActionB(QString const &name, int time, ContextPtr context) :
    IAction(context),
    _name(name),
    _time(time)
{
}

QString TestActionB::GetName()
{
    return _name;
}

/*void TestActionB::StartAction(Context &context)
{
}*/

/*void TestActionB::Run(Context &context)
{
}*/

void TestActionB::ProcessStartImpl()
{
    QTimer::singleShot(_time, this, [this](){ emit ActionFinished(); });
}

void TestActionB::ProcessStopImpl()
{
    // do nothing
}

}

