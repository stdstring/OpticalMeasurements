#include <QFile>
#include <QIODevice>
#include <QList>
#include <QString>
#include <QTextStream>

#include <stdexcept>

#include "ObjReader.h"
#include "Vertex3D.h"

namespace OpenGLDemo
{

namespace
{

constexpr QChar CommentStart = '#';
const QString VertexDescriptor("v");
const QString NormalDescriptor("vn");

QString ReadLine(QTextStream &stream)
{
    QString line = stream.readLine().trimmed();
    return (line.size() > 0 && line[0] == CommentStart) ? QString() : line;
}

Vertex3D ReadVertex(QTextStream &stream)
{
    Vertex3D vertex;
    stream >> vertex.X >> vertex.Y >> vertex.Z;
    return vertex;
}

Normal3D ReadNormal(QTextStream &stream)
{
    Normal3D normal;
    stream >> normal.X >> normal.Y >> normal.Z;
    return normal;
}

void ReadData(QString &line, QList<Vertex3D> &vertexList, QList<Normal3D> &normalList)
{
    QTextStream stream(&line, QIODevice::ReadOnly);
    // we using C locale
    stream.setLocale(QLocale::c());
    QString descriptor;
    stream >> descriptor;
    // TODO (std_string) : use more functional style
    if (VertexDescriptor == descriptor)
        vertexList.append(ReadVertex(stream));
    if (NormalDescriptor == descriptor)
        normalList.append(ReadNormal(stream));
}

}

QList<Vertex3DData> ReadObjSource(QString const &filename)
{
    QList<Vertex3D> vertexList;
    QList<Normal3D> normalList;
    QFile file(filename);
    file.open(QIODevice::ReadOnly);
    QTextStream stream(&file);
    while (!stream.atEnd())
    {
        QString line = ReadLine(stream);
        if (line.isEmpty())
            continue;
        ReadData(line, vertexList, normalList);
    }
    if (vertexList.size() != normalList.size())
        throw std::logic_error("Bad data file");
    QList<Vertex3DData> dest;
    for (unsigned int index = 0; index < vertexList.size(); ++index)
        dest.append(Vertex3DData(vertexList[index], normalList[index]));
    return dest;
}

}
