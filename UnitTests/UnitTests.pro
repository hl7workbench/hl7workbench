QT += testlib
QT -= gui

TARGET = unittests
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += UnitTests.cpp

DEFINES += SRCDIR=\\\"$$PWD/\\\"

INCLUDEPATH += ../Library

LIBS += -L../Library -lhl7workbench
PRE_TARGETDEPS = ../Library/libhl7workbench.a


include(../Global.pri)
