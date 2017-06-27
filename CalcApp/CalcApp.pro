TEMPLATE = subdirs

# projects
SUBDIRS += src/Common \
           src/Transport \
           src/TestServerCore \
           src/TestServerApp \
           src/MainApp \
           # Test actions
           src/TestSaveDataAction \
           src/TestInteractionAction \
           src/TestDataGeneratorAction \
           src/TestTotalDataConsumerAction \
           src/TestPartDataConsumerAction \
           src/TestTotalDataTransformAction \
           src/TestPartDataTransformAction \
           src/TestTotalDataFailedAction \
           src/TestPartDataFailedAction \
           # Stage2 actions
           src/SaveVertexDataAction \
    src/DataReceiverAction

# tests
#SUBDIRS += tests/TransportTests
