#include <QList>
#include <QMultiMap>
#include <QObject>
#include <QString>

#include <stdexcept>

#include "Common/CommonDefs.h"
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

ActionPtr TestTotalDataTransformActionFactory::Create(QString const &name, const QMultiMap<QString, QString> &args, ServiceLocatorPtr serviceLocator, ContextPtr context)
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
    return ActionPtr(new TestTotalDataTransformAction(name, sourceKey, destKey, context));
}

}
