QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

# Using C++17 standard
CONFIG += c++17

# Your custom version info
VERSION = 0.1

# Directories for builds
DESTDIR = dist
OBJECTS_DIR = build
UI_DIR = gen/ui
MOC_DIR = gen/moc
RCC_DIR = gen/rcc

# disables all the APIs deprecated before Qt 6.0.0
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000

# Directories that are searched when including header files, no need for explicit directories, e.g. #include "../../code/foo.h" in source files
INCLUDEPATH += $$PWD/include

# The source files (e.g. *.cpp)
SOURCES += \
    src/clock.cpp \
    src/fire_alarm.cpp \
    src/greenhouse/condition.cpp \
    src/greenhouse/greenhouse.cpp \
    src/greenhouse/greenhouse_create.cpp \
    src/greenhouse/plant.cpp \
    src/greenhouse/plant_group.cpp \
    src/greenhouse/plant_profile.cpp \
    src/log.cpp \
    src/main.cpp \
    src/note.cpp \
    src/notification.cpp \
    src/notification_control.cpp \
    src/sensors_actors/mock_environment.cpp \
    src/sensors_actors/sensor.cpp \
    src/sensors_actors/sensor_control.cpp \
    src/sensors_actors/water_control.cpp \
    src/sensors_actors/water_valve.cpp \
    src/ui/group_dialog.cpp \
    src/ui/log_window.cpp \
    src/ui/mainwindow.cpp \
    src/ui/plant_group_box.cpp \
    src/ui/plant_label.cpp \

# The header files (e.g. *.h)
HEADERS += \
    include/clock.h \
    include/date_time.h \
    include/fire_alarm.h \
    include/greenhouse/condition.h \
    include/greenhouse/greenhouse.h \
    include/greenhouse/greenhouse_create.h \
    include/greenhouse/plant.h \
    include/greenhouse/plant_group.h \
    include/greenhouse/plant_profile.h \
    include/log.h \
    include/note.h \
    include/notification.h \
    include/notification_control.h \
    include/sensors_actors/mock_environment.h \
    include/sensors_actors/sensor.h \
    include/sensors_actors/sensor_control.h \
    include/sensors_actors/water_control.h \
    include/sensors_actors/water_valve.h \
    include/ui/group_dialog.h \
    include/ui/log_window.h \
    include/ui/mainwindow.h \
    include/ui/plant_group_box.h \
    include/ui/plant_label.h

# The GUI definition files (so-called forms)
FORMS += \
    group_window.ui \
    mainwindow.ui

# Resources to integrate (e.g. images)
RESOURCES += \
    data/data.qrc
