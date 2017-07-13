#include <QList>
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
#include "TestDataGeneratorAction.h"
#include "TestDataGeneratorActionFactory.h"

namespace CalcApp
{

TestDataGeneratorActionFactory::TestDataGeneratorActionFactory(QObject *parent) : IActionFactory(parent)
{
}

QString TestDataGeneratorActionFactory::GetType()
{
    return "TestDataGeneratorAction";
}

ActionPtr TestDataGeneratorActionFactory::Create(QString const &name,
                                                 QMultiMap<QString, QString> const &args,
                                                 ServiceLocatorPtr serviceLocator,
                                                 ContextPtr context,
                                                 ExecutionStatePtr state)
{
    const QString keyName = "key";
    const QString sleepTimeName = "sleep_time";
    const QString dataCountName = "data_count";
    Q_UNUSED(serviceLocator);
    QString key = GetStringArgValue(args, keyName);
    int sleepTime = GetIntArgValue(args, sleepTimeName);
    int dataCount = GetIntArgValue(args, dataCountName);
    return ActionPtr(new TestDataGeneratorAction(name, key, sleepTime, dataCount, context, state));
}

}
