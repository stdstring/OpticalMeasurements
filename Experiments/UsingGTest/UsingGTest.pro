QT += core
QT -= gui

LIBS += -L../../gtest/lib -lgtest -lgtest_main -lgmock -lgmock_main
INCLUDEPATH += ../../gtest/include

TARGET = UsingGTest
CONFIG += console
CONFIG -= app_bundle
CONFIG += C++11

TEMPLATE = app

SOURCES += main.cpp \
           Calculator.cpp \
           ComplexCalculator.cpp \
           CalculatorDataTest.cpp \
           CalculatorTest.cpp \
           ComplexCalculatorTest.cpp

HEADERS += Calculator.h \
           ISimpleCalculator.h \
           ComplexCalculator.h

