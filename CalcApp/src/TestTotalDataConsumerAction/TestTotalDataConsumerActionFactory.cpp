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
#include "TestTotalDataConsumerAction.h"
#include "TestTotalDataConsumerActionFactory.h"

namespace CalcApp
{

TestTotalDataConsumerActionFactory::TestTotalDataConsumerActionFactory(QObject *parent) : IActionFactory(parent)
{
}

QString TestTotalDataConsumerActionFactory::GetType()
{
    return "TestTotalDataConsumerAction";
}

ActionPtr TestTotalDataConsumerActionFactory::Create(QString const &name,
                                                     QMultiMap<QString, QString> const &args,
                                                     ServiceLocatorPtr serviceLocator,
                                                     ContextPtr context,
                                                     ExecutionStatePtr state)
{
    const QString keyName = "key";
    const QString filenameName = "filename";
    Q_UNUSED(serviceLocator);
    QString key = GetStringArgValue(args, keyName);
    QString filename = GetStringArgValue(args, filenameName);
    return ActionPtr(new TestTotalDataConsumerAction(name, key, filename, context, state));
}

}
