QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

# Using C++17 standard
CONFIG += c++17

# Directories that are searched when including header files, no need for explicit directories, e.g. #include "../../code/foo.h" in source files
INCLUDEPATH += $$PWD/../app/include


# The source files (e.g. *.cpp)
SOURCES += \
    ../app/src/greenhouse/plant_group.cpp \
    testplantgroup.cpp

# The header files (e.g. *.h)
HEADERS += \
    ../app/include/greenhouse/plant_group.h \
    testplantgroup.h
