#include <QObject>
#include <QString>

#include "Common/CommonDefs.h"
#include "Common/Context.h"
#include "Common/IAction.h"
#include "Common/IActionFactory.h"
#include "Common/ServiceLocator.h"
#include "TestFailedAction.h"
#include "TestFailedActionFactory.h"

namespace CalcApp
{

TestFailedActionFactory::TestFailedActionFactory(QObject *parent) : IActionFactory(parent)
{
}

QString TestFailedActionFactory::GetId()
{
    return "TestFailedAction";
}

ActionPtr TestFailedActionFactory::Create(QString const &name, QString const &args, ServiceLocatorPtr serviceLocator, ContextPtr context)
{
    Q_UNUSED(serviceLocator);
    int time = args.toInt();
    return ActionPtr(new TestFailedAction(name, time, context));
}

}
