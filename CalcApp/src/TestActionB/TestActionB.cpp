#include <QObject>
#include <QString>
#include <QtGlobal>
#include <QTimer>

#include "Common/Context.h"
#include "Common/IAction.h"
#include "TestActionB.h"

namespace CalcApp
{

TestActionB::TestActionB(const QString &name, int time, QObject *parent) :
    IAction(parent),
    _name(name),
    _time(time)
{
}

QString TestActionB::GetName()
{
    return _name;
}

void TestActionB::StartAction(Context &context)
{
    Q_UNUSED(context);
    QTimer::singleShot(_time, this, [this](){ emit ActionFinished(); });
}

}

