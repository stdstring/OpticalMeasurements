#include <QMultiMap>
#include <QObject>
#include <QString>

#include <stdexcept>

#include "Common/CommonDefs.h"
#include "Common/Utils/ActionArgumentsHelper.h"
#include "Common/Context.h"
#include "Common/IAction.h"
#include "Common/IActionFactory.h"
#include "Common/ServiceLocator.h"
#include "TestPartDataFailedAction.h"
#include "TestPartDataFailedActionFactory.h"

namespace CalcApp
{

TestPartDataFailedActionFactory::TestPartDataFailedActionFactory(QObject *parent) : IActionFactory(parent)
{
}

QString TestPartDataFailedActionFactory::GetType()
{
    return "TestPartDataFailedAction";
}

ActionPtr TestPartDataFailedActionFactory::Create(QString const &name,
                                                  QMultiMap<QString, QString> const &args,
                                                  ServiceLocatorPtr serviceLocator,
                                                  ContextPtr context,
                                                  ExecutionStatePtr state)
{
    const QString sourceKeyName = "source_key";
    const QString destKeyName = "dest_key";
    const QString failedIterationName = "failed_iteration";
    Q_UNUSED(serviceLocator);
    QString sourceKey = GetStringArgValue(args, sourceKeyName);
    QString destKey = GetStringArgValue(args, destKeyName);
    int failedIteration = GetIntArgValue(args, failedIterationName);
    return ActionPtr(new TestPartDataFailedAction(name, sourceKey, destKey, failedIteration, context, state));
}

}
