#include <QApplication>
#include <QList>
#include <QDir>

//#include "MainWindow.h"
//#include "OpenGLSphereWidget.h"
#include "OpenGLXYZWidget.h"
#include "Vertex3D.h"
#include "XYZReader.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    //OpenGLDemo::OpenGLSphereWidget openGLSphere;
    //openGLSphere.resize(400, 400);
    //openGLSphere.show();
    //return app.exec();
    //OpenGLDemo::OpenGLXYZWidget *widget = new OpenGLDemo::OpenGLXYZWidget();
    //OpenGLDemo::MainWindow w(widget);
    //w.show();
    //return app.exec();
    //QList<OpenGLDemo::Vertex3D> data = OpenGLDemo::ReadXYZSource("demo.xyz");
    //QList<OpenGLDemo::Vertex3D> data = OpenGLDemo::ReadXYZSource("CylinderSmall.xyz");
    //QList<OpenGLDemo::Vertex3D> data = OpenGLDemo::ReadXYZSource("CylinderLarge.xyz");
    QList<OpenGLDemo::Vertex3D> data = OpenGLDemo::ReadXYZSource("rp.xyz");
    OpenGLDemo::OpenGLXYZWidget widget;
    widget.resize(400, 400);
    widget.show();
    widget.ShowData(data);
    return app.exec();
}
