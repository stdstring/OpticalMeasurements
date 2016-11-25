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
           CalculatorWidget.cpp \
           SimpleFakeCalculatorFactory.cpp

HEADERS += ..\CommonLib\ICalculator.h \
           ..\CommonLib\ICalculatorFactory.h \
           ..\CommonLib\ITransport.h \
           ..\CommonLib\Message.h \
           ..\CommonLib\MessageType.h \
           SimpleFakeCalculator.h \
           CalculatorWidget.h \
           SimpleFakeCalculatorFactory.h


DISTFILES += SimpleFakeCalculator.json

unix {
    target.path = /usr/lib
    INSTALLS += target
}

FORMS += CalculatorWidget.ui
