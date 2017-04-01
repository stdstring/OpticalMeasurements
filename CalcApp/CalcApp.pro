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
           src/TestInteractionAction

# tests
SUBDIRS += tests/TransportTests
