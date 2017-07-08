#pragma once

namespace CalcApp
{

struct EncodersData
{
public:
    EncodersData();

    int GlobalRotationX;
    int GlobalTransferX;
    int GlobalRotationY;
    int GlobalTransferY;
    int GlobalRotationZ;
    int GlobalTransferZ;
    int LocalRotation;
    int LocalTransfer;
    int SensorTransfer;
    int Value;
};

}
