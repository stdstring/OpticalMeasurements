#pragma once

namespace CalcApp
{

// TODO (std_string) : This set of encoders is specific for Stage2 only. Think about location of it
struct EncodersData
{
public:
    EncodersData();

    /*int GlobalRotationX;
    int GlobalTransferX;
    int GlobalRotationY;
    int GlobalTransferY;
    int GlobalRotationZ;
    int GlobalTransferZ;
    int LocalRotation;
    int LocalTransfer;
    int SensorTransfer;
    int Value;*/
    int GlobalTransferX;
    int GlobalTransferY;
    int GlobalTransferZ;
    int LocalRotation;
    int LocalTransfer;
    int SensorTransfer;
    int Value;
};

// TODO (std_string) : This set of encoders is specific for Stage2 only. Think about location of it
struct EncodersConstraints
{
public:
    EncodersConstraints();

    /*double GlobalTransferStep;
    int GlobalTransferMaxValue;
    double GlobalRotationStep;
    int GlobalRotationLength;
    double LocalTransferStep;
    int LocalTransferMaxValue;
    double LocalRotationStep;
    int LocalRotationLength;
    double SensorTransferStep;
    int SensorTransferMaxValue;
    double SensorResolution;*/
    double GlobalTransferStep;
    double LocalTransferStep;
    int LocalRotationLength;
    double SensorTransferStep;
    double SensorResolution;

};

}
