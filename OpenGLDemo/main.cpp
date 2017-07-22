#include <QApplication>

#include "MainWindow.h"
#include "OpenGLSphereWidget.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    OpenGLDemo::OpenGLSphereWidget openGLSphere;
    openGLSphere.resize(400, 400);
    openGLSphere.show();
    return app.exec();
    //OpenGLDemo::MainWindow w;
    //w.show();
    //return a.exec();
}
