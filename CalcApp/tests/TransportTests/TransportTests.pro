include(../../common.pri)
include(../../tests.pri)

QT += core network
#QT -= gui

TARGET = TransportTests
CONFIG += console
#CONFIG -= app_bundle

TEMPLATE = app

INCLUDEPATH += ../../include/Common
INCLUDEPATH += ../../include/TestServerCore
INCLUDEPATH += ../../../external/gtest/include

#LIBS += -lCommon -lTestServerCore -lTransport$${LIB_SUFFIX}
#LIBS += -lCommon -lTestServerCore -lTransport$${LIB_SUFFIX}
LIBS += -lCommon -lTestServerCore -lTransport$${LIB_SUFFIX}

#INCLUDEPATH += ../../include/
INCLUDEPATH += ../../src/Transport

#HEADERS += ../../include/Common/TransportConfig.h \
#           ../../include/TestServerCore/TestServerConfig.h \
#           ../../include/TestServerCore/TestServer.h \
#           ../../include/TestServerCore/TestServerRunner.h \
#           EqualityOperators.h \
#           MessageHelper.h \
#           TransportSignalHandler.h \
#           ClientHandler.h

HEADERS += EqualityOperators.h \
           MessageHelper.h \
           TransportSignalHandler.h \
           ClientHandler.h

#SOURCES += main.cpp \
#           MessageValidationTests.cpp \
#           MessageInfoFactoryTests.cpp \
#           SimpleMessageCheckStrategyTests.cpp \
#           DelayedMessagesProcessorTests.cpp \
#           EqualityOperators.cpp \
#           MessageHelper.cpp \
#           TransportTests.cpp \
#           TransportSignalHandler.cpp \
#           TransportFunctionalTests.cpp \
#           ClientHandler.cpp

SOURCES += main.cpp \
           EqualityOperators.cpp \
           MessageHelper.cpp \
           TransportSignalHandler.cpp \
           ClientHandler.cpp \
           MessageValidationTests.cpp \
           MessageInfoFactoryTests.cpp
