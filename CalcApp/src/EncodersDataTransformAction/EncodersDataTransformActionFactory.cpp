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
    const QString globalTransferStepName = "global_transfer_step";
    const QString localTransferStepName = "local_transfer_step";
    const QString localRotationLengthName = "local_rotation_length";
    const QString sensorTransferStepName = "sensor_transfer_step";
    const QString sensorResolutionName = "sensor_resolution";
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
    QList<QString> globalTransferStepData = args.values(globalTransferStepName);
    if (globalTransferStepData.size() != 1)
        throw std::invalid_argument(globalTransferStepName.toStdString());
    double globalTransferStep = globalTransferStepData[0].toDouble(&ok);
    if (!ok)
        throw std::invalid_argument(globalTransferStepName.toStdString());
    QList<QString> localTransferStepData = args.values(localTransferStepName);
    if (localTransferStepData.size() != 1)
        throw std::invalid_argument(localTransferStepName.toStdString());
    double localTransferStep = localTransferStepData[0].toDouble(&ok);
    if (!ok)
        throw std::invalid_argument(localTransferStepName.toStdString());
    QList<QString> localRotationLengthData = args.values(localRotationLengthName);
    if (localRotationLengthData.size() != 1)
        throw std::invalid_argument(localRotationLengthName.toStdString());
    int localRotationLength = localRotationLengthData[0].toInt(&ok);
    if (!ok)
        throw std::invalid_argument(localRotationLengthName.toStdString());
    QList<QString> sensorTransferStepData = args.values(sensorTransferStepName);
    if (sensorTransferStepData.size() != 1)
        throw std::invalid_argument(sensorTransferStepName.toStdString());
    double sensorTransferStep = sensorTransferStepData[0].toDouble(&ok);
    if (!ok)
        throw std::invalid_argument(sensorTransferStepName.toStdString());
    QList<QString> sensorResolutionData = args.values(sensorResolutionName);
    if (sensorResolutionData.size() != 1)
        throw std::invalid_argument(sensorResolutionName.toStdString());
    double sensorResolution = sensorResolutionData[0].toDouble(&ok);
    if (!ok)
        throw std::invalid_argument(sensorResolutionName.toStdString());
    EncodersConstraints constraints(globalTransferStep, localTransferStep, localRotationLength, sensorTransferStep, sensorResolution);
    return ActionPtr(new EncodersDataTransformAction(name, sourceKey, destKey, constraints, context, state));
}

}
