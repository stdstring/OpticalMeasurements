#pragma once

namespace CalcApp
{

struct Vertex3D
{
public:
    Vertex3D();
    Vertex3D(double x, double y, double z);

    double X;
    double Y;
    double Z;
};

// TODO (std_string) : This set of encoders is specific for Stage2 only. Think about location of it
struct Vertex3DData
{
public:
    Vertex3DData();
    Vertex3DData(Vertex3D const &surfacePoint, Vertex3D const &sensor);

    Vertex3D SurfacePoint;
    Vertex3D Sensor;
};

}
