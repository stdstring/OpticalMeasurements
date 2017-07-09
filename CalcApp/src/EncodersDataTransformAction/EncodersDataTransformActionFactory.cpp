#include <QMultiMap>
#include <QObject>
#include <QString>

#include <stdexcept>

#include "Common/CommonDefs.h"
#include "Common/Data/EncodersData.h"
#include "Common/Context.h"
#include "Common/IAction.h"
#include "Common/IActionFactory.h"
#include "Common/ServiceLocator.h"
#include "EncodersDataTransformAction.h"
#include "EncodersDataTransformActionFactory.h"

namespace CalcApp
{

EncodersDataTransformActionFactory::EncodersDataTransformActionFactory(QObject *parent) : IActionFactory(parent)
{
}

QString EncodersDataTransformActionFactory::GetType()
{
    return "EncodersDataTransformAction";
}

ActionPtr EncodersDataTransformActionFactory::Create(QString const &name,
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
    // TODO (std_string) : create reading data for encoders constraints
    EncodersConstraints constraints;
    return ActionPtr(new EncodersDataTransformAction(name, sourceKey, destKey, constraints, context, state));
}

}
