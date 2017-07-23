#include <QApplication>

#include "MainWindow.h"
//#include "OpenGLSphereWidget.h"
#include "OpenGLXYZWidget.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    //OpenGLDemo::OpenGLSphereWidget openGLSphere;
    //openGLSphere.resize(400, 400);
    //openGLSphere.show();
    //return app.exec();
    OpenGLDemo::MainWindow w(new OpenGLDemo::OpenGLXYZWidget());
    w.show();
    return app.exec();
}
