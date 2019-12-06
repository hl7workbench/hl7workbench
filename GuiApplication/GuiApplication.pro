QT += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = hl7workbench
TEMPLATE = app

HEADERS += MainWindow.h

SOURCES += main.cpp \
           MainWindow.cpp

FORMS += MainWindow.ui

include(../Global.pri)
