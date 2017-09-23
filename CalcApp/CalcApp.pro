TEMPLATE = subdirs

# projects
#SUBDIRS += src/Common \
#           src/Transport \
#           src/TestServerCore \
#           src/TestServerApp \
#           src/MainApp \
#           # Test actions
#           src/TestSaveDataAction \
#           src/TestInteractionAction \
#           src/TestDataGeneratorAction \
#           src/TestTotalDataConsumerAction \
#           src/TestPartDataConsumerAction \
#           src/TestTotalDataTransformAction \
#           src/TestPartDataTransformAction \
#           src/TestTotalDataFailedAction \
#           src/TestPartDataFailedAction \
#           # Stage2 actions
#           src/SaveVertexDataAction \
#           src/DataReceiverAction \
#           src/EncodersDataTransformAction \
#           src/Stage2DataGenerator \
#           # Viewers
#           src/SimpleTextViewer

# tests
#SUBDIRS += tests/TransportTests

#CONFIG += ordered

# projects
SUBDIRS += Common \
           Transport \
           TestServerCore \
           TestServerApp \
           MainApp \
           # Test actions
           TestSaveDataAction \
           TestInteractionAction \
           TestDataGeneratorAction \
           TestTotalDataConsumerAction \
           TestPartDataConsumerAction \
           TestTotalDataTransformAction \
           TestPartDataTransformAction \
           TestTotalDataFailedAction \
           TestPartDataFailedAction \
           # Stage2 actions
           SaveVertexDataAction \
           DataReceiverAction \
           EncodersDataTransformAction \
           Stage2DataGenerator \
           # Viewers
           SimpleTextViewer

# tests
SUBDIRS += TransportTests

# Common
Common.subdir = src/Common
# Transport
Transport.subdir = src/Transport
Transport.depends = Common
# TestServerCore
TestServerCore.subdir = src/TestServerCore
TestServerCore.depends = Common
# TestServerApp
TestServerApp.subdir = src/TestServerApp
TestServerApp.depends = Common TestServerCore
# MainApp
MainApp.subdir = src/MainApp
MainApp.depends = Common
# TestSaveDataAction
TestSaveDataAction.subdir = src/TestSaveDataAction
TestSaveDataAction.depends = Common
# TestInteractionAction
TestInteractionAction.subdir = src/TestInteractionAction
TestInteractionAction.depends = Common
# TestDataGeneratorAction
TestDataGeneratorAction.subdir = src/TestDataGeneratorAction
TestDataGeneratorAction.depends = Common
# TestTotalDataConsumerAction
TestTotalDataConsumerAction.subdir = src/TestTotalDataConsumerAction
TestTotalDataConsumerAction.depends = Common
# TestPartDataConsumerAction
TestPartDataConsumerAction.subdir = src/TestPartDataConsumerAction
TestPartDataConsumerAction.depends = Common
# TestTotalDataTransformAction
TestTotalDataTransformAction.subdir = src/TestTotalDataTransformAction
TestTotalDataTransformAction.depends = Common
# TestPartDataTransformAction
TestPartDataTransformAction.subdir = src/TestPartDataTransformAction
TestPartDataTransformAction.depends = Common
# TestTotalDataFailedAction
TestTotalDataFailedAction.subdir = src/TestTotalDataFailedAction
TestTotalDataFailedAction.depends = Common
# TestPartDataFailedAction
TestPartDataFailedAction.subdir = src/TestPartDataFailedAction
TestPartDataFailedAction.depends = Common
# SaveVertexDataAction
SaveVertexDataAction.subdir = src/SaveVertexDataAction
SaveVertexDataAction.depends = Common
# DataReceiverAction
DataReceiverAction.subdir = src/DataReceiverAction
DataReceiverAction.depends = Common
# EncodersDataTransformAction
EncodersDataTransformAction.subdir = src/EncodersDataTransformAction
EncodersDataTransformAction.depends = Common
# Stage2DataGenerator
Stage2DataGenerator.subdir = src/Stage2DataGenerator
Stage2DataGenerator.depends = Common
# SimpleTextViewer
SimpleTextViewer.subdir = src/SimpleTextViewer
# TransportTests
TransportTests.subdir = tests/TransportTests
TransportTests.depends = Transport TestServerCore Common
