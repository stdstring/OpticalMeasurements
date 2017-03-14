#include <QObject>
#include <QString>
#include <QtGlobal>
#include <QTimer>

#include "Common/Context.h"
#include "Common/IAction.h"
#include "TestActionA.h"

namespace CalcApp
{

TestActionA::TestActionA(const QString &name, int time, QObject *parent) :
    IAction(parent),
    _name(name),
    _time(time)
{
}

QString TestActionA::GetName()
{
    return _name;
}

void TestActionA::StartAction(Context &context)
{
    Q_UNUSED(context);
    QTimer::singleShot(_time, this, [this](){ emit ActionFinished(); });
}

}

