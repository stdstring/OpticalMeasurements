#include <QObject>
#include <QString>

#include "Common/Context.h"
#include "Common/IAction.h"
#include "TestInteractionAction.h"

namespace CalcApp
{

TestInteractionAction::TestInteractionAction(QString const &name, QObject *parent) :
    IAction(parent),
    _name(name)
{
}

QString TestInteractionAction::GetName()
{
    return _name;
}

void TestInteractionAction::Run(Context &context)
{
}

}
