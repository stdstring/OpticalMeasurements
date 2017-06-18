#include <QMultiMap>
#include <QObject>
#include <QString>

#include <stdexcept>

#include "Common/CommonDefs.h"
#include "Common/Context.h"
#include "Common/IAction.h"
#include "Common/IActionFactory.h"
#include "Common/ServiceLocator.h"
#include "TestPartDataTransformAction.h"
#include "TestPartDataTransformActionFactory.h"

namespace CalcApp
{

TestPartDataTransformActionFactory::TestPartDataTransformActionFactory(QObject *parent) : IActionFactory(parent)
{
}

QString TestPartDataTransformActionFactory::GetType()
{
    return "TestPartDataTransformAction";
}

ActionPtr TestPartDataTransformActionFactory::Create(QString const &name,
                                                     QMultiMap<QString, QString> const &args,
                                                     ServiceLocatorPtr serviceLocator,
                                                     ContextPtr context,
                                                     ExecutionStatePtr state)
{
    const QString sourceKeyName = "source_key";
    const QString destKeyName = "dest_key";
    Q_UNUSED(serviceLocator);
    QList<QString> sourceKeyData = args.values(sourceKeyName);
    if (sourceKeyData.size() != 1)
        throw std::invalid_argument(sourceKeyName.toStdString());
    QString sourceKey = sourceKeyData[0];
    QList<QString> destKeyData = args.values(destKeyName);
    if (destKeyData.size() != 1)
        throw std::invalid_argument(destKeyName.toStdString());
    QString destKey = destKeyData[0];
    return ActionPtr(new TestPartDataTransformAction(name, sourceKey, destKey, context, state));
}

}
