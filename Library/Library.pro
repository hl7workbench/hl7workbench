QT += network xml
QT -= gui

TARGET = hl7workbench
TEMPLATE = lib
CONFIG += staticlib

HEADERS += Library.h

SOURCES += Library.cpp


unix {
    target.path = /usr/lib
    INSTALLS += target
}

include(../Global.pri)
