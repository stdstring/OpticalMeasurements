include( ../../common.pri )
include( ../../lib.pri )

QT += core

TARGET = Common
TEMPLATE = lib
CONFIG += staticlib

INCLUDEPATH += ../../include/Common

SOURCES += ComponentLoader.cpp \
           Context.cpp \
           ComponentStorage.cpp \
           ActionChainFactory.cpp \
           TransportSerialization.cpp

HEADERS += ../../include/Common/ActionChainFactory.h \
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
           ../../include/Common/TransportSerialization.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
