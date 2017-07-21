#pragma once

#include <QList>
#include <QString>

#include "Vertex3D.h"

namespace OpenGLDemo
{

QList<Vertex3D> ReadXYZSource(QString const &filename);

}
