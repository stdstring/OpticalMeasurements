#include <QObject>
#include <QString>

#include <memory>

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

std::shared_ptr<IAction> TestFailedActionFactory::Create(QString const &name,
                                                         QString const &args,
                                                         std::shared_ptr<ServiceLocator> serviceLocator,
                                                         std::shared_ptr<Context> context)
{
    Q_UNUSED(serviceLocator);
    int time = args.toInt();
    return std::shared_ptr<IAction>(new TestFailedAction(name, time, context));
}

}
