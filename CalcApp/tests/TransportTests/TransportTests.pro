include( ../../common.pri )
include( ../../tests.pri )

QT += core network
QT -= gui

TARGET = TransportTests
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

LIBS += -lCommon -lTestServerCore -lTransport$${LIB_SUFFIX}

INCLUDEPATH += ../../src/Transport

HEADERS += ../../include/Common/TransportConfig.h \
           ../../include/TestServerCore/TestServerConfig.h \
           ../../include/TestServerCore/TestServer.h \
           ../../include/TestServerCore/TestServerRunner.h \
           EqualityOperators.h \
           MessageHelper.h \
           TransportSignalHandler.h \
           ClientEntry.h \
           ClientHandler.h

SOURCES += main.cpp \
           MessageValidationTests.cpp \
           MessageInfoFactoryTests.cpp \
           SimpleMessageCheckStrategyTests.cpp \
           DelayedMessagesProcessorTests.cpp \
           EqualityOperators.cpp \
           MessageHelper.cpp \
           TransportTests.cpp \
           TransportSignalHandler.cpp \
           TransportFunctionalTests.cpp \
           ClientHandler.cpp
