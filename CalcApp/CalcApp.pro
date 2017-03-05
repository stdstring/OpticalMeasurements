TEMPLATE = subdirs

# projects
SUBDIRS += src/Common \
           src/Transport \
           src/TestServerCore \
           src/TestServerApp \
           src/MainApp

# tests
SUBDIRS += tests/TransportTests
