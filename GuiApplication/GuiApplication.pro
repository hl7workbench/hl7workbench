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

QT += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = hl7workbench
TEMPLATE = app

HEADERS += MainWindow.h \
    Hl7MessageEditorTabWidget.h \
    Hl7MessageEditorWidget.h \
    Hl7GuiCommon.h

SOURCES += main.cpp \
           MainWindow.cpp \
    Hl7MessageEditorTabWidget.cpp \
    Hl7MessageEditorWidget.cpp

FORMS += MainWindow.ui

unix {
    target.path = /usr/bin
    INSTALLS += target
}

include(../Global.pri)
