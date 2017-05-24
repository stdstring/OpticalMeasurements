#include <QObject>
#include <QString>

#include "Common/CommonDefs.h"
#include "Common/Context.h"
#include "Common/IAction.h"
#include "Common/IActionFactory.h"
#include "Common/ServiceLocator.h"
#include "TestDataGeneratorAction.h"
#include "TestDataGeneratorActionFactory.h"

namespace CalcApp
{

TestDataGeneratorActionFactory::TestDataGeneratorActionFactory(QObject *parent) : IActionFactory(parent)
{
}

QString TestDataGeneratorActionFactory::GetId()
{
    return "TestDataGeneratorAction";
}

ActionPtr TestDataGeneratorActionFactory::Create(QString const &name, QString const &args, ServiceLocatorPtr serviceLocator, ContextPtr context)
{
    Q_UNUSED(args);
    Q_UNUSED(serviceLocator);
    return ActionPtr(new TestDataGeneratorAction(name, context));
}

}
