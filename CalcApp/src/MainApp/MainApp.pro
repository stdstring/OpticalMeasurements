include( ../../common.pri )
include( ../../app.pri )

QT       += core gui xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MainApp
TEMPLATE = app

LIBS += -lCommon

SOURCES += main.cpp \
           MainWindow.cpp \
           StateManager.cpp \
           ActionManager.cpp \
           DefaultConfigReader.cpp \
           ActionExecuter.cpp \
           XmlConfigReader.cpp \
           CommandLineDefs.cpp \
           ChooseResultDialog.cpp

HEADERS  += MainWindow.h \
            StateManager.h \
            ActionManager.h \
            DefaultConfigReader.h \
            ActionExecuter.h \
            XmlConfigReader.h \
            CommandLineDefs.h \
            ChooseResultDialog.h

FORMS    += MainWindow.ui \
            ChooseResultDialog.ui

DISTFILES += MainApp_Test.conf
