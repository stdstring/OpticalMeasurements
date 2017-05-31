TEMPLATE = subdirs

# projects
SUBDIRS += src/Common \
           src/Transport \
           src/TestServerCore \
           src/TestServerApp \
           src/TestActionA \
           src/TestActionB \
           src/TestFailedAction \
           src/MainApp \
           src/TestSaveDataAction \
           src/TestInteractionAction \
           src/TestDataGeneratorAction \
           src/TestTotalDataConsumerAction \
           src/TestPartDataConsumerAction \
           src/TestTotalDataTransformAction \
           src/TestPartDataTransformAction

# tests
#SUBDIRS += tests/TransportTests
