include(../../common.pri)
include(../../tests.pri)

QT += core network

TARGET = TransportTests
CONFIG += console

TEMPLATE = app

INCLUDEPATH += ../../include/Common
INCLUDEPATH += ../../include/TestServerCore
INCLUDEPATH += ../../../external/gtest/include
INCLUDEPATH += ../../src/Transport

LIBS += -lTransport$${LIB_SUFFIX} -lTestServerCore -lCommon

HEADERS += EqualityOperators.h \
           MessageHelper.h \
           TransportSignalHandler.h \
           ClientHandler.h \
           DelayedMessagesProcessorHandler.h

SOURCES += main.cpp \
           EqualityOperators.cpp \
           MessageHelper.cpp \
           TransportSignalHandler.cpp \
           ClientHandler.cpp \
           MessageValidationTests.cpp \
           MessageInfoFactoryTests.cpp \
           SimpleMessageCheckStrategyTests.cpp \
           DelayedMessagesProcessorTests.cpp \
           TransportTests.cpp \
           TransportFunctionalTests.cpp \
           DelayedMessagesProcessorHandler.cpp
