include( ../../common.pri )
include( ../../lib.pri )

QT += core

TARGET = Common
TEMPLATE = lib
CONFIG += staticlib

INCLUDEPATH += ../../include/Common

SOURCES += DefaultConfigReader.cpp \
           ComponentLoader.cpp \
           Context.cpp \
           ComponentStorage.cpp

HEADERS += ../../include/Common/IAction.h \
           ../../include/Common/IActionFactory.h \
           ../../include/Common/ActionsConfig.h \
           ../../include/Common/ComponentLoader.h \
           ../../include/Common/ComponentStorage.h \
           ../../include/Common/Context.h \
           ../../include/Common/DefaultConfigReader.h \
           ../../include/Common/IComponentInfo.h \
           ../../include/Common/IConfigReader.h \
           ../../include/Common/ITransport.h \
           ../../include/Common/ITransportFactory.h \
           ../../include/Common/MainConfig.h \
           ../../include/Common/Message.h \
           ../../include/Common/TransportConfig.h \

unix {
    target.path = /usr/lib
    INSTALLS += target
}
