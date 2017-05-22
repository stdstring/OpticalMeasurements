#include <QObject>
#include <QString>

#include "Common/CommonDefs.h"
#include "Common/Context.h"
#include "Common/IAction.h"
#include "Common/IActionFactory.h"
#include "Common/ServiceLocator.h"
#include "TestActionB.h"
#include "TestActionBFactory.h"

namespace CalcApp
{

TestActionBFactory::TestActionBFactory(QObject *parent) : IActionFactory(parent)
{
}

QString TestActionBFactory::GetId()
{
    return "TestActionB";
}

ActionPtr TestActionBFactory::Create(QString const &name, QString const &args, ServiceLocatorPtr serviceLocator, ContextPtr context)
{
    Q_UNUSED(serviceLocator);
    int time = args.toInt();
    return ActionPtr(new TestActionB(name, time, context));
}

}
