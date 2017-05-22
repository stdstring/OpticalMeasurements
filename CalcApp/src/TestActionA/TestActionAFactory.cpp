#include <QObject>
#include <QString>

#include "Common/CommonDefs.h"
#include "Common/Context.h"
#include "Common/IAction.h"
#include "Common/IActionFactory.h"
#include "Common/ServiceLocator.h"
#include "TestActionA.h"
#include "TestActionAFactory.h"

namespace CalcApp
{

TestActionAFactory::TestActionAFactory(QObject *parent) : IActionFactory(parent)
{
}

QString TestActionAFactory::GetId()
{
    return "TestActionA";
}

ActionPtr TestActionAFactory::Create(QString const &name, QString const &args, ServiceLocatorPtr serviceLocator, ContextPtr context)
{
    Q_UNUSED(serviceLocator);
    int time = args.toInt();
    return ActionPtr(new TestActionA(name, time, context));
}

}
