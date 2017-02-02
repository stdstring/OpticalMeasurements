include( ../../common.pri )
include( ../../tests.pri )

QT += core
QT -= gui

TARGET = TransportTests
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

LIBS += -L../../lib.$${OS_SUFFIX} -lTransport$${LIB_SUFFIX}
INCLUDEPATH += ../../src/Transport

HEADERS += ../../include/Message.h


SOURCES += main.cpp \
           MessageValidationTests.cpp \
           MessageInfoFactoryTests.cpp \
           SimpleMessageCheckStrategyTests.cpp \
    DelayedMessagesProcessorTests.cpp
