#include "Vertex3D.h"

namespace CalcApp
{

Vertex3D::Vertex3D() : X(0), Y(0), Z(0)
{
}

Vertex3D::Vertex3D(double x, double y, double z) : X(x), Y(y), Z(z)
{
}

Vertex3DData::Vertex3DData()
{
}

Vertex3DData::Vertex3DData(Vertex3D const &surfacePoint, Vertex3D const &sensor) :
    SurfacePoint(surfacePoint),
    Sensor(sensor)
{
}

}
