#
# This file is part of the HL7 Workbench project.
#
# Copyright (C) 2019  Individual HL7 Workbench contributors.
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
#  the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
#

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
