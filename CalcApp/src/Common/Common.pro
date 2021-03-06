include(../../common.pri)
include(../../lib.pri)

QT += core

TARGET = Common
TEMPLATE = lib
CONFIG += staticlib

INCLUDEPATH += ../../include/Common
INCLUDEPATH += ../../include/Common/Data
INCLUDEPATH += ../../include/Common/Logger
INCLUDEPATH += ../../include/Common/LinearAlgebra
INCLUDEPATH += ../../include/Common/Utils

# Armadillo
INCLUDEPATH += ../../../external/armadillo/include

SOURCES += Data/EncodersData.cpp \
           Data/Vertex3D.cpp \
           LinearAlgebra/Matrix.cpp \
           LinearAlgebra/MatrixFactory.cpp \
           Logger/LoggerService.cpp \
           Logger/NullLogger.cpp \
           Logger/QMessageLoggerWrapper.cpp \
           Logger/ConsoleLogger.cpp \
           Utils/ActionArgumentsHelper.cpp \
           ComponentLoader.cpp \
           Context.cpp \
           ComponentStorage.cpp \
           ActionChainFactory.cpp \
           TransportSerialization.cpp \
           ServiceLocator.cpp \
           TransportService.cpp \
           TransportServiceFactory.cpp \
           IAction.cpp \
           ExecutionState.cpp

HEADERS += ../../include/Common/Data/EncodersData.h \
           ../../include/Common/Data/Vertex3D.h \
           ../../include/Common/Exception/NotImplementedException.h \
           ../../include/Common/LinearAlgebra/Matrix.h \
           ../../include/Common/LinearAlgebra/MatrixFactory.h \
           ../../include/Common/Logger/ILogger.h \
           ../../include/Common/Logger/LoggerService.h \
           ../../include/Common/Logger/NullLogger.h \
           ../../include/Common/Logger/QMessageLoggerWrapper.h \
           ../../include/Common/Logger/ConsoleLogger.h \
           ../../include/Common/Utils/ActionArgumentsHelper.h \
           ../../include/Common/ActionChainFactory.h \
           ../../include/Common/ActionsConfig.h \
           ../../include/Common/ComponentLoader.h \
           ../../include/Common/ComponentStorage.h \
           ../../include/Common/Context.h \
           ../../include/Common/ExecutionState.h \
           ../../include/Common/IAction.h \
           ../../include/Common/IActionFactory.h \
           ../../include/Common/IComponentInfo.h \
           ../../include/Common/IConfigReader.h \
           ../../include/Common/ITransport.h \
           ../../include/Common/ITransportFactory.h \
           ../../include/Common/Lazy.h \
           ../../include/Common/MainConfig.h \
           ../../include/Common/Message.h \
           ../../include/Common/TransportConfig.h \
           ../../include/Common/TransportSerialization.h \
           ../../include/Common/ServiceLocator.h \
           ../../include/Common/ExceptionData.h \
           ../../include/Common/CommonDefs.h \
           TransportService.h \
           TransportServiceFactory.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
