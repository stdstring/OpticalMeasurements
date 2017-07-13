#include <QMultiMap>
#include <QObject>
#include <QString>

#include <stdexcept>

#include "Common/CommonDefs.h"
#include "Common/Data/EncodersData.h"
#include "Common/Utils/ActionArgumentsHelper.h"
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
    QString sourceKey = GetStringArgValue(args, sourceKeyName);
    QString destKey = GetStringArgValue(args, destKeyName);
    double globalTransferStep = GetDoubleArgValue(args, globalTransferStepName);
    double localTransferStep = GetDoubleArgValue(args, localTransferStepName);
    int localRotationLength = GetIntArgValue(args, localRotationLengthName);
    double sensorTransferStep = GetDoubleArgValue(args, sensorTransferStepName);
    double sensorResolution = GetDoubleArgValue(args, sensorResolutionName);
    EncodersConstraints constraints(globalTransferStep, localTransferStep, localRotationLength, sensorTransferStep, sensorResolution);
    return ActionPtr(new EncodersDataTransformAction(name, sourceKey, destKey, constraints, context, state));
}

}
