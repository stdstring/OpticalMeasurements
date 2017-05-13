#include <QObject>
#include <QString>
#include <QTimer>

#include <memory>

#include "Common/Context.h"
#include "Common/IAction.h"
#include "TestActionA.h"

namespace CalcApp
{

TestActionA::TestActionA(QString const &name, int time, std::shared_ptr<Context> context) :
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
    Q_UNUSED(context);
    QTimer::singleShot(_time, this, [this](){ emit ActionFinished(); });
}*/

/*void TestActionA::Run(Context &context)
{
    Q_UNUSED(context);
    QThread::msleep(_time);
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

