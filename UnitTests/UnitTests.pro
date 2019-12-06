QT += testlib
QT -= gui

TARGET = unittests
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += UnitTests.cpp

DEFINES += SRCDIR=\\\"$$PWD/\\\"

include(../Global.pri)
