#include "EncodersData.h"

namespace CalcApp
{

// TODO (std_string) : This set of encoders is specific for Stage2 only. Think about location of it
EncodersData::EncodersData() :
    /*GlobalRotationX(0),
    GlobalTransferX(0),
    GlobalRotationY(0),
    GlobalTransferY(0),
    GlobalRotationZ(0),
    GlobalTransferZ(0),
    LocalRotation(0),
    LocalTransfer(0),
    SensorTransfer(0),
    Value(0)*/
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
EncodersConstraints::EncodersConstraints() :
    /*GlobalTransferStep(0),
    GlobalTransferMaxValue(0),
    GlobalRotationStep(0),
    GlobalRotationLength(0),
    LocalTransferStep(0),
    LocalTransferMaxValue(0),
    LocalRotationStep(0),
    LocalRotationLength(0),
    SensorTransferStep(0),
    SensorTransferMaxValue(0),
    SensorResolution(0)*/
    GlobalTransferStep(0),
    LocalTransferStep(0),
    LocalRotationLength(0),
    SensorTransferStep(0),
    SensorResolution(0)
{
}

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
