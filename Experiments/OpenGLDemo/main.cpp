#include <QApplication>
#include <QList>
#include <QDir>

//#include "MainWindow.h"
#include "OpenGLXYZWidget.h"
#include "OpenGLObjWidget.h"
#include "Vertex3D.h"
#include "ObjReader.h"
#include "XYZReader.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    //QList<OpenGLDemo::Vertex3D> data = OpenGLDemo::ReadXYZSource("CylinderSmall.xyz");
    //QList<OpenGLDemo::Vertex3D> data = OpenGLDemo::ReadXYZSource("CylinderLarge.xyz");
    //QList<OpenGLDemo::Vertex3D> data = OpenGLDemo::ReadXYZSource("ThreadLargeExample.xyz");
    //QList<OpenGLDemo::Vertex3DData> data = OpenGLDemo::ReadObjSource("CylinderSmallData.obj");
    QList<OpenGLDemo::Vertex3DData> data = OpenGLDemo::ReadObjSource("CylinderLargeData.obj");
    //OpenGLDemo::OpenGLXYZWidget widget;
    OpenGLDemo::OpenGLObjWidget widget;
    widget.resize(400, 400);
    widget.show();
    widget.ShowData(data);
    return app.exec();
}
