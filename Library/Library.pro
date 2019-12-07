QT += network xml
QT -= gui

TARGET = hl7workbench
TEMPLATE = lib
CONFIG += staticlib

HEADERS += Library.h \
    Hl7Message.h \
    Hl7Segment.h \
    Hl7Component.h \
    Hl7SubComponent.h \
    Hl7EncodingCharacters.h \
    Hl7Field.h \
    Hl7MessagePart.h

SOURCES += Library.cpp \
    Hl7Message.cpp \
    Hl7Segment.cpp \
    Hl7Component.cpp \
    Hl7SubComponent.cpp \
    Hl7EncodingCharacters.cpp \
    Hl7Field.cpp \
    Hl7MessagePart.cpp


unix {
    target.path = /usr/lib
    INSTALLS += target
}

include(../Global.pri)
