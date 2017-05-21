#include <QObject>
#include <QString>

#include <memory>

#include "Common/Exception/NotImplementedException.h"
#include "Common/Context.h"
#include "Common/IAction.h"
#include "Common/IActionFactory.h"
#include "Common/ServiceLocator.h"
#include "TestDataDependentActionFactory.h"

namespace CalcApp
{

TestDataDependentActionFactory::TestDataDependentActionFactory(QObject *parent) : IActionFactory(parent)
{
}

QString TestDataDependentActionFactory::GetId()
{
    return "TestDataDependentAction";
}

std::shared_ptr<IAction> TestDataDependentActionFactory::Create(QString const &name,
                                                                QString const &args,
                                                                std::shared_ptr<ServiceLocator> serviceLocator,
                                                                std::shared_ptr<Context> context)
{
    Q_UNUSED(name);
    Q_UNUSED(args);
    Q_UNUSED(serviceLocator);
    Q_UNUSED(context);
    throw NotImplementedException();
}

}

