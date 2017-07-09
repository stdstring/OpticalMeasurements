#define _USE_MATH_DEFINES

#include <QObject>
#include <QReadLocker>
#include <QString>
#include <QWriteLocker>

#include <cmath>
#include <initializer_list>
#include <memory>

#include "Common/CommonDefs.h"
#include "Common/Data/EncodersData.h"
#include "Common/Data/Vertex3D.h"
#include "Common/LinearAlgebra/Matrix.h"
#include "Common/LinearAlgebra/MatrixFactory.h"
#include "Common/Context.h"
#include "Common/IAction.h"
#include "EncodersDataTransformAction.h"

namespace CalcApp
{

namespace
{

typedef QListContextItem<EncodersData> EncodersDataContextItem;
typedef QListContextItem<Vertex3D> Vertex3DContextItem;

Vertex3D CreateVertex(EncodersData const &data, EncodersConstraints const &constraints)
{
    double globalTransferX = data.GlobalTransferX * constraints.GlobalTransferStep;
    double globalTransferY = data.GlobalTransferY * constraints.GlobalTransferStep;
    double globalTransferZ = data.GlobalTransferZ * constraints.GlobalTransferStep;
    double globalRotationLength = constraints.GlobalRotationLength * constraints.GlobalRotationStep;
    double globalRotationX = (2 * M_PI * data.GlobalRotationX * constraints.GlobalRotationStep) / globalRotationLength;
    double globalRotationY = (2 * M_PI * data.GlobalRotationY * constraints.GlobalRotationStep) / globalRotationLength;
    double globalRotationZ = (2 * M_PI * data.GlobalRotationZ * constraints.GlobalRotationStep) / globalRotationLength;
    double localTransfer = data.LocalTransfer * constraints.LocalTransferStep;
    double localRotationLength = constraints.LocalRotationLength * constraints.LocalRotationStep;
    double localRotation = (2 * M_PI * data.LocalRotation * constraints.LocalRotationStep) / localRotationLength;
    double sensorTransfer = data.SensorTransfer * constraints.SensorTransferStep;
    double sensorValue = data.Value * constraints.SensorResolution;
    Matrix localValueColumn = Matrix::CreateColumnMatrix({0, 0, sensorValue, 1});
    Matrix globalValueColumn = CreateXRotationMatrix(globalRotationX) *
                               CreateXTransferMatrix(globalTransferX) *
                               CreateYRotationMatrix(globalRotationY) *
                               CreateYTransferMatrix(globalTransferY) *
                               CreateZRotationMatrix(globalRotationZ) *
                               CreateZTransferMatrix(globalTransferZ) *
                               CreateZRotationMatrix(localRotation) *
                               CreateXTransferMatrix(localTransfer) *
                               CreateXTransferMatrix(sensorTransfer) *
                               localValueColumn;
    return Vertex3D(globalValueColumn.GetValue(0, 0), globalValueColumn.GetValue(1, 0), globalValueColumn.GetValue(2, 0));
}

void TransformData(EncodersDataContextItem *sourceItem, Vertex3DContextItem *destItem, int start, EncodersConstraints const &constraints)
{
    QReadLocker _readLocker(&sourceItem->Lock);
    QWriteLocker _writeLocker(&destItem->Lock);
    bool transformed = false;
    for (int index = start; index < sourceItem->Data.length(); ++index)
    {
        transformed = true;
        EncodersData sourceValue = sourceItem->Data[index];
        Q_UNUSED(sourceValue);
        // TODO (std_string) : add transformation from EncodersData into Vertex3D
        destItem->Data.append(CreateVertex(sourceValue, constraints));
    }
    if (transformed)
        emit destItem->NotifyDataChange();
}

}

EncodersDataTransformAction::EncodersDataTransformAction(QString const &name,
                                                         QString const &sourceKey,
                                                         QString const &destKey,
                                                         EncodersConstraints const &constraints,
                                                         ContextPtr context,
                                                         ExecutionStatePtr state) :
    IAction(context, state),
    _name(name),
    _sourceKey(sourceKey),
    _destKey(destKey),
    _constraints(constraints)
{
    context.get()->Set(_destKey, std::make_shared<Vertex3DContextItem>(new Vertex3DContextItem()));
}

QString EncodersDataTransformAction::GetName()
{
    return _name;
}

/*void EncodersDataTransformAction::StartAction(Context &context)
{
}*/

/*void EncodersDataTransformAction::Run(Context &context)
{
}*/

void EncodersDataTransformAction::ProcessStartImpl()
{
    ContextPtr context = GetContext();
    QObject::connect(context.get(), &Context::DataChanged, this, [this](QString const &key){
        if (key == _sourceKey)
            ProcessData();
    });
    QObject::connect(context.get(), &Context::DataCompleted, this, [this](QString const &key){
        if (key == _sourceKey)
            FinishProcessData();
    });
    _index = -1;
}

void EncodersDataTransformAction::ProcessStopImpl()
{
    // do nothing
}

void EncodersDataTransformAction::CleanupNonFinished()
{
    // do nothing
}

void EncodersDataTransformAction::ProcessData()
{
    ProcessData(GetContext());
}

void EncodersDataTransformAction::FinishProcessData()
{
    ContextPtr context = GetContext();
    ProcessData(context);
    emit context.get()->DataCompleted(_destKey);
    emit ActionFinished();
}

void EncodersDataTransformAction::ProcessData(ContextPtr context)
{
    EncodersDataContextItem *sourceItem = context.get()->GetValue<EncodersDataContextItem>(_sourceKey);
    Vertex3DContextItem *destItem = context.get()->GetValue<Vertex3DContextItem>(_destKey);
    TransformData(sourceItem, destItem, _index + 1, _constraints);
    _index = sourceItem->Data.length() - 1;
}

}
