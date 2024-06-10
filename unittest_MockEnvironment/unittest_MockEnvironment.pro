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
    ../app/src/sensors_actors/mock_environment.cpp \
    testmockenvironment.cpp

# The header files (e.g. *.h)
HEADERS += \
    ../app/include/sensors_actors/mock_environment.h \
    ../app/include/sensors_actors/sensor_control.h \
    ../app/include/sensors_actors/water_control.h \
    testmockenvironment.h
