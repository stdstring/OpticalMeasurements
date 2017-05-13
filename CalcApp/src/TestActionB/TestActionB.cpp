#include <QObject>
#include <QString>
#include <QTimer>

#include <memory>

#include "Common/Context.h"
#include "Common/IAction.h"
#include "TestActionB.h"

namespace CalcApp
{

TestActionB::TestActionB(QString const &name, int time, std::shared_ptr<Context> context) :
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
    Q_UNUSED(context);
    QTimer::singleShot(_time, this, [this](){ emit ActionFinished(); });
}*/

/*void TestActionB::Run(Context &context)
{
    Q_UNUSED(context);
    QThread::msleep(_time);
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

