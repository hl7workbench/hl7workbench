TEMPLATE = subdirs

SUBDIRS += \
    GuiApplication \
    Library \
    UnitTests

OTHER_FILES = .gitignore \
              Global.pri

GuiApplication.depends = Library
UnitTests.depends = Library

