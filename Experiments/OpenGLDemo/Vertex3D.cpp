#include "Vertex3D.h"

namespace OpenGLDemo
{

Vertex3D::Vertex3D() : X(0), Y(0), Z(0)
{
}

Vertex3D::Vertex3D(double x, double y, double z) : X(x), Y(y), Z(z)
{
}

Normal3D::Normal3D() : X(0), Y(0), Z(0)
{
}

Normal3D::Normal3D(double x, double y, double z) : X(x), Y(y), Z(z)
{
}

Vertex3DData::Vertex3DData()
{
}

Vertex3DData::Vertex3DData(Vertex3D const &vertex, Normal3D const &normal) : Vertex(vertex), Normal(normal)
{
}

}
