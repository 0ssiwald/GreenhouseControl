#include "greenhouse/greenhouse.h"
#include "ui/mainwindow.h"
#include "sensors_actors/mock_environment.h"
#include "clock.h"
#include "log.h"
#include "sensors_actors/sensor_control.h"
#include "notification_control.h"
#include "sensors_actors/water_control.h"
#include "greenhouse/greenhouse_create.h"
#include "fire_alarm.h"

#include <QApplication>
#include <QSettings>
#include <QCommandLineParser>
#include <QtDebug>
#include <QDir>
#include <QObject>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    // Is it fine to access the jsons via qrc file ??????????????
    Q_INIT_RESOURCE(data);
    // Create Greenhouse
    GreenhouseCreate ghc;
    Greenhouse* greenhouse = ghc.loadGreenhouseFromFile(":/greenhouse.json");
    // If there is a problem with the json file this is a alternative that should work
    //Greenhouse* greenhouse = ghc.createGreenhouseFromCode();

    //Create Log
    SystemLog log;
    // Saves the log in file instead of the console output
    // Is it fine that the logs are created in the build folder????????????????
    //log.initLogging();

    //Create notifications
    NotificationControl notificationControl;
    //notificationControl.loadNotificationsFromFile(":/notifications.json");
    // This is also a alternative to reading the notifications from json for testing
    notificationControl.createAllNotificationsForAllPlants(greenhouse);

    // Create Control Classes
    TemperatureSensor temperature_sensor;
    HumiditySensor humidity_sensor;
    SensorControl sensorControl(&temperature_sensor, &humidity_sensor, greenhouse);
    WaterValve main_valve(true);
    FlowSensor flow_sensor;
    WaterControl waterControl(&main_valve, &flow_sensor, greenhouse);
    // Create a mock environment
    MockEnvironment mockEnvironment(&sensorControl, &waterControl);
    // Create Fire Alarm
    FireAlarm fireAlarm;

    // Init GUI
    MainWindow window(greenhouse, &log, &notificationControl, &waterControl, &sensorControl);
    window.show();

    int seconds_between_notification_update = 5;
    int seconds_between_measurements = 1;
    // Init Clocks
    physics::Clock sensorClock(seconds_between_measurements);
    physics::Clock notificationClock(seconds_between_notification_update);
    // Measure temperature every clock cycle
    QObject::connect(&sensorClock, &physics::Clock::update, &sensorControl, &SensorControl::measureTemperature);
    // Connect the signal from the SensorControl class to the updateTemperatureLabel slot in the MainWindow class
    QObject::connect(&sensorControl, &SensorControl::temperatureMeasured, &window, &MainWindow::updateTemperatureLabel);
    QObject::connect(&sensorControl, &SensorControl::temperatureMeasured, &mockEnvironment, &MockEnvironment::generateNewTemperature);
    // Same for humidity
    QObject::connect(&sensorClock, &physics::Clock::update, &sensorControl, &SensorControl::measureHumidity);
    QObject::connect(&sensorControl, &SensorControl::humidityMeasured, &window, &MainWindow::updateHumidityLabel);
    QObject::connect(&sensorControl, &SensorControl::humidityMeasured, &mockEnvironment, &MockEnvironment::generateNewHumidity);
    // Same for soil moisture
    QObject::connect(&sensorClock, &physics::Clock::update, &sensorControl, &SensorControl::measureSoilMoistures);
    QObject::connect(&sensorControl, &SensorControl::soilMoisturesMeasured, &window, &MainWindow::updatePlantLabels);
    QObject::connect(&sensorControl, &SensorControl::updateSoilMoisture, &mockEnvironment, &MockEnvironment::generateNewSoilMoisture);
    // Update notifications
    QObject::connect(&notificationClock, &physics::Clock::update, &notificationControl, &NotificationControl::updateActiveNotificationList);
    QObject::connect(&notificationControl, &NotificationControl::updateNotificationListInUi, &window, &MainWindow::setNotificationList);
    // Control the moisture levels
    QObject::connect(&sensorClock, &physics::Clock::update, &waterControl, &WaterControl::controlMoistureLevels);
    QObject::connect(&waterControl, &WaterControl::mainValveWasClosed,  &window, &MainWindow::toggleMainValveToggleButtonOff);
    QObject::connect(&waterControl, &WaterControl::updateFlow, &mockEnvironment, &MockEnvironment::generateNewFlow);
    QObject::connect(&waterControl, &WaterControl::moistureLevelsControled, &window, &MainWindow::changeWaterSlider);
    QObject::connect(&waterControl, &WaterControl::moistureLevelsControled, &window, &MainWindow::updatePlantLabels);
    // Feueralarm
    QObject::connect(&fireAlarm, &FireAlarm::sendAlarm, &window, &MainWindow::fireAlarm);
    QObject::connect(&window, &MainWindow::fireAlarmTriggered, &fireAlarm, &FireAlarm::sendAlarm);

    sensorClock.start();
    notificationClock.start();

    return app.exec();
}
