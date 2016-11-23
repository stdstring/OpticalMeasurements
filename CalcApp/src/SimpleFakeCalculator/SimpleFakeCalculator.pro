#-------------------------------------------------
#
# Project created by QtCreator 2016-11-21T08:10:34
#
#-------------------------------------------------

QT       += core widgets

TARGET = SimpleFakeCalculator
TEMPLATE = lib
CONFIG += plugin c++11

#DESTDIR = $$[QT_INSTALL_PLUGINS]/generic

SOURCES += SimpleFakeCalculator.cpp \
           CalculatorWidget.cpp

HEADERS += ..\CommonLib\ICalculator.h \
           SimpleFakeCalculator.h \
           CalculatorWidget.h


DISTFILES += SimpleFakeCalculator.json

unix {
    target.path = /usr/lib
    INSTALLS += target
}

FORMS += CalculatorWidget.ui
