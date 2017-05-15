#include "MainWindow.h"
#include <QApplication>

#include "CustomExceptionData.h"
#include "CustomMessageData.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qRegisterMetaType<CustomSignalData::CustomMessageData>("CustomMessageData");
    //qRegisterMetaType<CustomSignalData::CustomMessageData>("CustomSignalData::CustomMessageData");
    //qRegisterMetaType<CustomMessageData>();
    qRegisterMetaType<CustomSignalData::CustomExceptionData>("CustomExceptionData");
    //qRegisterMetaType<CustomSignalData::CustomExceptionData>("CustomSignalData::CustomExceptionData");
    //qRegisterMetaType<CustomExceptionData>();
    CustomSignalData::MainWindow w;
    w.show();
    return a.exec();
}
