#include <QApplication>

#include "MainWindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CalcApp::MainWindow w;
    w.show();
    return a.exec();
}
