#include <QFile>
#include <QIODevice>
#include <QLocale>
#include <QObject>
#include <QReadLocker>
#include <QString>
#include <QTextStream>

#include <cmath>

#include "Common/CommonDefs.h"
#include "Common/Data/Vertex3D.h"
#include "Common/Context.h"
#include "Common/IAction.h"
#include "SaveVertexDataAction.h"

namespace CalcApp
{

namespace
{

typedef QListContextItem<Vertex3DData> Vertex3DDataContextItem;

// TODO (std_string) : think about location and value of this const
constexpr int RealNumberPrecision = 8;

void WriteData(QTextStream &vertexListStream, QTextStream &normalListStream, Vertex3DDataContextItem *item, int start)
{
    QReadLocker locker(&item->Lock);
    for (int index = start; index < item->Data.length(); ++index)
    {
        Vertex3D surfacePoint  = item->Data[index].SurfacePoint;
        Vertex3D sensor  = item->Data[index].Sensor;
        // TODO (std_string) : probably create class for Vectors
        double vectorX = sensor.X - surfacePoint.X;
        double vectorY = sensor.Y - surfacePoint.Y;
        double vectorZ = sensor.Z - surfacePoint.Z;
        double vectorLength = sqrt(vectorX * vectorX + vectorY * vectorY + vectorZ * vectorZ);
        double normalX = vectorX / vectorLength;
        double normalY = vectorY / vectorLength;
        double normalZ = vectorZ / vectorLength;
        vertexListStream << "# vertex " << index + 1 << endl;
        vertexListStream << "v " << surfacePoint.X << " " << surfacePoint.Y << " " << surfacePoint.Z << endl;
        normalListStream << "# vertex " << index + 1 << endl;
        normalListStream << "vn " << normalX << " " << normalY << " " << normalZ << endl;
    }
}

void WriteData(QString *vertexList, QString *normalList, Vertex3DDataContextItem *item, int start)
{
    QTextStream vertexListStream(vertexList, QIODevice::Append);
    QTextStream normalListStream(normalList, QIODevice::Append);
    // we using C locale
    vertexListStream.setLocale(QLocale::c());
    normalListStream.setLocale(QLocale::c());
    // set real number params
    vertexListStream.setRealNumberNotation(QTextStream::RealNumberNotation::FixedNotation);
    vertexListStream.setRealNumberPrecision(RealNumberPrecision);
    normalListStream.setRealNumberNotation(QTextStream::RealNumberNotation::FixedNotation);
    normalListStream.setRealNumberPrecision(RealNumberPrecision);
    WriteData(vertexListStream, normalListStream, item, start);
}

void SaveData(QString const &filename, QString const &vertexList, QString const &normalList)
{
    QFile file(filename);
    file.open(QIODevice::WriteOnly);
    QTextStream stream(&file);
    stream << "# begin" << endl << endl;
    stream << "# vertex list" << endl;
    stream << vertexList << endl;
    stream << "# normal list" << endl;
    stream << normalList << endl;
    stream << "# end" << endl;
}

}

SaveVertexDataAction::SaveVertexDataAction(QString const &actionName, QString const &key, QString const &filename, ContextPtr context, ExecutionStatePtr state) :
    IAction(context, state),
    _actionName(actionName),
    _key(key),
    _filename(filename)
{
}

QString SaveVertexDataAction::GetName()
{
    return _actionName;
}

/*void SaveVertexDataAction::StartAction(Context &context)
{
}*/

/*void SaveVertexDataAction::Run(Context &context)
{
}*/

void SaveVertexDataAction::ProcessStartImpl()
{
    ContextPtr context = GetContext();
    QObject::connect(context.get(), &Context::DataChanged, this, [this](QString const &key){
        if (key == _key)
            ProcessData();
    });
    QObject::connect(context.get(), &Context::DataCompleted, this, [this](QString const &key){
        if (key == _key)
            FinishProcessData();
    });
    _index = -1;
}

void SaveVertexDataAction::ProcessStopImpl()
{
}

void SaveVertexDataAction::CleanupNonFinished()
{
    QFile::remove(_filename);
}

void SaveVertexDataAction::ProcessData()
{
    ProcessDataImpl();
}

void SaveVertexDataAction::FinishProcessData()
{
    ProcessDataImpl();
    SaveData(_filename, _vertexList, _normalList);
    emit ActionFinished();
}

void SaveVertexDataAction::ProcessDataImpl()
{
    ContextPtr context = GetContext();
    Vertex3DDataContextItem *item = context.get()->GetValue<Vertex3DDataContextItem>(_key);
    WriteData(&_vertexList, &_normalList, item, _index + 1);
    _index = item->Data.length() - 1;
}

}
