include( ../../common.pri )
include( ../../lib.pri )

QT += core

TARGET = Common
TEMPLATE = lib
CONFIG += staticlib

INCLUDEPATH += ../../include/Common
INCLUDEPATH += ../../include/Common/Logger

SOURCES += ComponentLoader.cpp \
           Context.cpp \
           ComponentStorage.cpp \
           ActionChainFactory.cpp \
           TransportSerialization.cpp \
           Logger/QMessageLoggerWrapper.cpp \
           ServiceLocator.cpp

HEADERS += ../../include/Common/Logger/ILogger.h \
           ../../include/Common/Logger/NullLogger.h \
           ../../include/Common/Logger/QMessageLoggerWrapper.h \
           ../../include/Common/ActionChainFactory.h \
           ../../include/Common/ActionsConfig.h \
           ../../include/Common/ComponentLoader.h \
           ../../include/Common/ComponentStorage.h \
           ../../include/Common/Context.h \
           ../../include/Common/IAction.h \
           ../../include/Common/IActionFactory.h \
           ../../include/Common/IComponentInfo.h \
           ../../include/Common/IConfigReader.h \
           ../../include/Common/ITransport.h \
           ../../include/Common/ITransportFactory.h \
           ../../include/Common/MainConfig.h \
           ../../include/Common/Message.h \
           ../../include/Common/TransportConfig.h \
           ../../include/Common/TransportSerialization.h \
           ../../include/Common/ServiceLocator.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
