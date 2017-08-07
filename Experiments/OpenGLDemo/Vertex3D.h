#pragma once

namespace OpenGLDemo
{

struct Vertex3D
{
public:
    Vertex3D();
    Vertex3D(double x, double y, double z);

    double X, Y, Z;
};

struct Normal3D
{
public:
    Normal3D();
    Normal3D(double x, double y, double z);

    double X, Y, Z;
};

struct Vertex3DData
{
public:
    Vertex3DData();
    Vertex3DData(Vertex3D const &vertex, Normal3D const &normal);

    Vertex3D Vertex;
    Normal3D Normal;
};

}
