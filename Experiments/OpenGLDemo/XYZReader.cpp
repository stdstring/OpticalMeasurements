#include <QFile>
#include <QIODevice>
#include <QList>
#include <QString>
#include <QTextStream>

#include "Vertex3D.h"
#include "XYZReader.h"

namespace OpenGLDemo
{

namespace
{

constexpr QChar CommentStart = '#';

QString ReadLine(QTextStream &stream)
{
    QString line = stream.readLine().trimmed();
    return (line.size() > 0 && line[0] == CommentStart) ? QString() : line;
}

Vertex3D ReadVertex(QString &line)
{
    QTextStream stream(&line, QIODevice::ReadOnly);
    // we using C locale
    stream.setLocale(QLocale::c());
    Vertex3D vertex;
    stream >> vertex.X >> vertex.Y >> vertex.Z;
    return vertex;
}

}

QList<Vertex3D> ReadXYZSource(QString const &filename)
{
    QList<Vertex3D> dest;
    QFile file(filename);
    file.open(QIODevice::ReadOnly);
    QTextStream stream(&file);
    while (!stream.atEnd())
    {
        QString line = ReadLine(stream);
        if (line.isEmpty())
            continue;
        dest.append(ReadVertex(line));
    }
    return dest;
}

}
