#include "EncodersData.h"

namespace CalcApp
{

// TODO (std_string) : This set of encoders is specific for Stage2 only. Think about location of it
EncodersData::EncodersData() :
    GlobalTransferX(0),
    GlobalTransferY(0),
    GlobalTransferZ(0),
    LocalRotation(0),
    LocalTransfer(0),
    SensorTransfer(0),
    Value(0)
{
}

// TODO (std_string) : This set of encoders is specific for Stage2 only. Think about location of it
EncodersData::EncodersData(int globalTransferX,
                           int globalTransferY,
                           int globalTransferZ,
                           int localRotation,
                           int localTransfer,
                           int sensorTransfer,
                           int value) :
    GlobalTransferX(globalTransferX),
    GlobalTransferY(globalTransferY),
    GlobalTransferZ(globalTransferZ),
    LocalRotation(localRotation),
    LocalTransfer(localTransfer),
    SensorTransfer(sensorTransfer),
    Value(value)
{
}

// TODO (std_string) : This set of encoders is specific for Stage2 only. Think about location of it
EncodersConstraints::EncodersConstraints() :
    GlobalTransferStep(0),
    LocalTransferStep(0),
    LocalRotationLength(0),
    SensorTransferStep(0),
    SensorResolution(0)
{
}

// TODO (std_string) : This set of encoders is specific for Stage2 only. Think about location of it
EncodersConstraints::EncodersConstraints(double globalTransferStep,
                                         double localTransferStep,
                                         int localRotationLength,
                                         double sensorTransferStep,
                                         double SensorResolution) :
    GlobalTransferStep(globalTransferStep),
    LocalTransferStep(localTransferStep),
    LocalRotationLength(localRotationLength),
    SensorTransferStep(sensorTransferStep),
    SensorResolution(SensorResolution)
{

}

}
