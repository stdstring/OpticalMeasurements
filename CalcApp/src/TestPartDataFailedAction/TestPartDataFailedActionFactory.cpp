#include <QMultiMap>
#include <QObject>
#include <QString>

#include <stdexcept>

#include "Common/CommonDefs.h"
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

ActionPtr TestPartDataFailedActionFactory::Create(QString const &name, const QMultiMap<QString, QString> &args, ServiceLocatorPtr serviceLocator, ContextPtr context)
{
    const QString sourceKeyName = "source_key";
    const QString destKeyName = "dest_key";
    const QString failedIterationName = "failed_iteration";
    Q_UNUSED(serviceLocator);
    bool ok;
    QList<QString> sourceKeyData = args.values(sourceKeyName);
    if (sourceKeyData.size() != 1)
        throw std::invalid_argument(sourceKeyName.toStdString());
    QString sourceKey = sourceKeyData[0];
    QList<QString> destKeyData = args.values(destKeyName);
    if (destKeyData.size() != 1)
        throw std::invalid_argument(destKeyName.toStdString());
    QString destKey = destKeyData[0];
    QList<QString> failedIterationData = args.values(failedIterationName);
    if (failedIterationData.size() != 1)
        throw std::invalid_argument(failedIterationName.toStdString());
    int failedIteration = failedIterationData[0].toInt(&ok);
    if (!ok)
        throw std::invalid_argument(failedIterationName.toStdString());
    return ActionPtr(new TestPartDataFailedAction(name, sourceKey, destKey, failedIteration, context));
}

}
