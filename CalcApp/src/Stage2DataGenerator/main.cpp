#define _USE_MATH_DEFINES

#include <QByteArray>
#include <QDataStream>
#include <QFile>
#include <QIODevice>
#include <QList>
#include <QPair>
#include <QString>
#include <QTextStream>

#include <cmath>
#include <cstdlib>
#include <time.h>

#include "Common/Data/EncodersData.h"
#include "Common/Data/Vertex3D.h"
#include "Common/CommonDefs.h"

// encoders constraints
constexpr double GlobalTransferStep = 1.0;
constexpr double LocalTransferStep = 1.0;
constexpr int LocalRotationLength = 200;
constexpr double SensorTransferStep = 1.0;
constexpr double SensorResolution = 1.0;

// generation params
constexpr int RotationCount = 20;
constexpr int RotationDelta = LocalRotationLength / RotationCount;
constexpr int LayerCount = 10;
constexpr int LayerDelta = 5;
constexpr int CylinderRadius = 1000;
constexpr int SensorXMin = 100;
constexpr int SensorXMax = 200;
constexpr int SensorHMin = 10;
constexpr int SensorHMax = 80;

// output params
const QString filename = "data.conf";

QByteArray GetEncodersData(CalcApp::EncodersData const &encoders)
{
    QByteArray dest;
    QDataStream stream(&dest, QIODevice::WriteOnly);
    stream.setVersion(CalcApp::DataStreamVersion);
    stream << encoders.GlobalTransferX
           << encoders.GlobalTransferY
           << encoders.GlobalTransferZ
           << encoders.LocalRotation
           << encoders.LocalTransfer
           << encoders.SensorTransfer
           << encoders.Value;
    return dest;
}

QByteArray GetDataBody(int packageNumber, int calcNumber, CalcApp::EncodersData const &encoders)
{
    QByteArray dest;
    QDataStream stream(&dest, QIODevice::WriteOnly);
    stream.setVersion(CalcApp::DataStreamVersion);
    stream << packageNumber << calcNumber << GetEncodersData(encoders);
    return dest;
}

// Generate only for cylinder
int main(int argc, char *argv[])
{
    Q_UNUSED(argc);
    Q_UNUSED(argv);
    srand(time(nullptr));
    QList<QPair<CalcApp::Vertex3D, CalcApp::EncodersData>> dest;
    for (int layerIndex = 0; layerIndex < LayerCount; ++layerIndex)
    {
        int zValue = layerIndex * LayerDelta;
        double zCoord = zValue * GlobalTransferStep;
        for (int rotationIndex = 0; rotationIndex < RotationCount; ++rotationIndex)
        {
            int rotation = rotationIndex * RotationDelta;
            double angle = (2 * M_PI * rotationIndex) / RotationCount;
            double xCoord = CylinderRadius * GlobalTransferStep * cos(angle);
            double yCoord = CylinderRadius * GlobalTransferStep * sin(angle);
            // TODO (std_string) : think about randomizing of data
            int sensorShift = SensorXMin + (SensorXMax - SensorXMin) / 2;
            int sensorValue = SensorHMin + (SensorHMax - SensorHMin) / 2;
            int transferRadius = CylinderRadius - sensorShift - sensorValue;
            double xTransferCoord = transferRadius * GlobalTransferStep * cos(angle);
            double yTransferCoord = transferRadius * GlobalTransferStep * sin(angle);
            int xValue = std::round(xTransferCoord / GlobalTransferStep);
            int yValue = std::round(yTransferCoord / GlobalTransferStep);
            CalcApp::Vertex3D vertex(xCoord, yCoord, zCoord);
            CalcApp::EncodersData encoders(xValue, yValue, zValue, rotation, sensorShift, 0, sensorValue);
            dest.append(qMakePair(vertex, encoders));
        }
    }
    QFile file(filename);
    file.open(QIODevice::WriteOnly);
    QTextStream stream(&file);
    for (int index = 0; index < dest.size(); ++index)
    {
        int vertexNumber = index + 1;
        int packageNumber = index + 1;
        int calcNumber = 0;
        QPair<CalcApp::Vertex3D, CalcApp::EncodersData> data = dest.at(index);
        CalcApp::Vertex3D vertex = data.first;
        CalcApp::EncodersData encoders = data.second;
        stream << "# vertex " << vertexNumber << " : x = " << vertex.X << " y = " << vertex.Y << " z = " << vertex.Z << endl;
        stream << "# encoders : GlobalTransferX = " << encoders.GlobalTransferX
               << " GlobalTransferY = " << encoders.GlobalTransferY
               << " GlobalTransferZ = " << encoders.GlobalTransferZ
               << " LocalRotation = " << encoders.LocalRotation
               << " LocalTransfer = " << encoders.LocalTransfer
               << " SensorTransfer = " << encoders.SensorTransfer
               << " SensorValue = " << encoders.Value
               << endl;
        stream << "DATA HEX " << QString::fromUtf8(GetDataBody(packageNumber, calcNumber, encoders).toHex()) << endl;
    }
}
