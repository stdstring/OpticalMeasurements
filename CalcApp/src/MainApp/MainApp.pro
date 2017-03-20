include( ../../common.pri )
include( ../../app.pri )

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MainApp
TEMPLATE = app

LIBS += -lCommon

SOURCES += main.cpp \
           MainWindow.cpp \
           StateManager.cpp \
           ActionManager.cpp \
           DefaultConfigReader.cpp

HEADERS  += MainWindow.h \
            StateManager.h \
            ActionManager.h \
            DefaultConfigReader.h

FORMS    += MainWindow.ui
