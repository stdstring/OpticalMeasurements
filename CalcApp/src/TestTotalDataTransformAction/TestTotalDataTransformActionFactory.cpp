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
#include "TestTotalDataTransformAction.h"
#include "TestTotalDataTransformActionFactory.h"

namespace CalcApp
{

TestTotalDataTransformActionFactory::TestTotalDataTransformActionFactory(QObject *parent) : IActionFactory(parent)
{
}

QString TestTotalDataTransformActionFactory::GetType()
{
    return "TestTotalDataTransformAction";
}

ActionPtr TestTotalDataTransformActionFactory::Create(QString const &name,
                                                      QMultiMap<QString, QString> const &args,
                                                      ServiceLocatorPtr serviceLocator,
                                                      ContextPtr context,
                                                      ExecutionStatePtr state)
{
    const QString sourceKeyName = "source_key";
    const QString destKeyName = "dest_key";
    Q_UNUSED(serviceLocator);
    QString sourceKey = GetStringArgValue(args, sourceKeyName);
    QString destKey = GetStringArgValue(args, destKeyName);
    return ActionPtr(new TestTotalDataTransformAction(name, sourceKey, destKey, context, state));
}

}
