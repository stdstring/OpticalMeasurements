TEMPLATE = subdirs

# projects
SUBDIRS += src/Common \
           src/Transport \
           src/TestServerCore \
           src/TestServerApp \
           src/TestFailedAction \
           src/MainApp \
           src/TestSaveDataAction \
           src/TestInteractionAction \
           src/TestDataGeneratorAction \
           src/TestTotalDataConsumerAction \
           src/TestPartDataConsumerAction \
           src/TestTotalDataTransformAction \
           src/TestPartDataTransformAction \
           src/TestTotalDataFailedAction \
           src/TestPartDataFailedAction

# tests
#SUBDIRS += tests/TransportTests
