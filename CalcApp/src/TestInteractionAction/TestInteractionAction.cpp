#include <QObject>
#include <QString>

#include "Common/Context.h"
#include "Common/IAction.h"
#include "TestInteractionAction.h"

namespace CalcApp
{

TestInteractionAction::TestInteractionAction(QString const &actionName, QString const &contextKey, QObject *parent) :
    IAction(parent),
    _actionName(actionName),
    _contextKey(contextKey)
{
}

QString TestInteractionAction::GetName()
{
    return _actionName;
}

void TestInteractionAction::Run(Context &context)
{
    Q_UNUSED(context);
}

}
