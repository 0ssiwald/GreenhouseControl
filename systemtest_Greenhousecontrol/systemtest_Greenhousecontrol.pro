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
    ../app/src/clock.cpp \
    ../app/src/fire_alarm.cpp \
    ../app/src/greenhouse/condition.cpp \
    ../app/src/greenhouse/greenhouse.cpp \
    ../app/src/greenhouse/greenhouse_create.cpp \
    ../app/src/greenhouse/plant.cpp \
    ../app/src/greenhouse/plant_group.cpp \
    ../app/src/greenhouse/plant_profile.cpp \
    ../app/src/log.cpp \
    ../app/src/note.cpp \
    ../app/src/notification.cpp \
    ../app/src/notification_control.cpp \
    ../app/src/sensors_actors/mock_environment.cpp \
    ../app/src/sensors_actors/sensor.cpp \
    ../app/src/sensors_actors/sensor_control.cpp \
    ../app/src/sensors_actors/water_control.cpp \
    ../app/src/sensors_actors/water_valve.cpp \
    testgreenhousecontrol.cpp

# The header files (e.g. *.h)
HEADERS += \
    ../app/include/clock.h \
    ../app/include/date_time.h \
    ../app/include/fire_alarm.h \
    ../app/include/greenhouse/condition.h \
    ../app/include/greenhouse/greenhouse.h \
    ../app/include/greenhouse/greenhouse_create.h \
    ../app/include/greenhouse/plant.h \
    ../app/include/greenhouse/plant_group.h \
    ../app/include/greenhouse/plant_profile.h \
    ../app/include/log.h \
    ../app/include/note.h \
    ../app/include/notification.h \
    ../app/include/notification_control.h \
    ../app/include/sensors_actors/mock_environment.h \
    ../app/include/sensors_actors/sensor.h \
    ../app/include/sensors_actors/sensor_control.h \
    ../app/include/sensors_actors/water_control.h \
    ../app/include/sensors_actors/water_valve.h \
    testgreenhousecontrol.h
