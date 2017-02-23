include( ../../common.pri )
include( ../../tests.pri )

QT += core network
QT -= gui

TARGET = TransportTests
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

LIBS += -L../../lib.$${OS_SUFFIX} -lTransport$${LIB_SUFFIX}
INCLUDEPATH += ../../src/Transport

HEADERS += ../../include/ITransport.h \
           ../../include/Message.h \
           EqualityOperators.h \
           MessageHelper.h \
           TransportSignalHandler.h \
           TestServer.h


SOURCES += main.cpp \
           MessageValidationTests.cpp \
           MessageInfoFactoryTests.cpp \
           SimpleMessageCheckStrategyTests.cpp \
           DelayedMessagesProcessorTests.cpp \
           EqualityOperators.cpp \
           MessageHelper.cpp \
           TransportTests.cpp \
           TransportSignalHandler.cpp \
           TestServer.cpp \
           TransportFunctionalTests.cpp
