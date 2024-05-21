#include "greenhouse/greenhouse.h"
#include "ui/mainwindow.h"
#include "control/mock_enviroment.h"
#include "clock.h"
#include "log.h"
#include "control/sensor_control.h"
#include "notification_control.h"
#include "control/water_control.h"

#include <QApplication>
#include <QSettings>
#include <QCommandLineParser>
#include <QtDebug>
#include <QDir>
#include <QObject>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    // Create Greenhouse
    GreenhouseCreate ghc;
    std::shared_ptr<Greenhouse> greenhouse = ghc.createGreenhouseFromCode();
    //qDebug() << *greenhouse;

    //Create Log
    std::shared_ptr<SystemLog> log = std::make_shared<SystemLog>();
    log->initLogging();

    //Create notifications
    NotificationControl notificationControl(greenhouse);

    // Create Control Classes
    SensorControl sensorControl(greenhouse);
    WaterControl waterControl(greenhouse);
    // Create a mock environment
    MockEnvironment mockEnviroment(greenhouse, &sensorControl, &waterControl);


    // Init GUI
    MainWindow window(greenhouse, log, &notificationControl, &waterControl);
    window.show();

    int seconds_between_notification_update = (60 * 60);
    int seconds_between_measurments = 2;
    // Init Clocks
    physics::Clock sensorClock(seconds_between_measurments);
    physics::Clock notificationClock(seconds_between_notification_update);
    // Measure temperature every clock cycle
    QObject::connect(&sensorClock, &physics::Clock::update, &sensorControl, &SensorControl::measureTemperature);
    // Connect the signal from the SensorControl class to the updateTemperatureLabel slot in the MainWindow class
    QObject::connect(&sensorControl, &SensorControl::temperatureMeasured, &window, &MainWindow::updateTemperatureLabel);
    // Same for humidity
    QObject::connect(&sensorClock, &physics::Clock::update, &sensorControl, &SensorControl::measureHumidity);
    QObject::connect(&sensorControl, &SensorControl::humidityMeasured, &window, &MainWindow::updateHumidityLabel);
    // Same for soil moisture
    QObject::connect(&sensorClock, &physics::Clock::update, &sensorControl, &SensorControl::measureSoilMoistures);
    QObject::connect(&sensorControl, &SensorControl::soilMoisturesMeasured, &window, &MainWindow::updatePlantLabels);
    // Update notifications
    QObject::connect(&notificationClock, &physics::Clock::update, &notificationControl, &NotificationControl::updateNotificationList);
    QObject::connect(&notificationControl, &NotificationControl::updateNotificationListInUi, &window, &MainWindow::setNotificationList);
    // Control the moisture levels
    QObject::connect(&sensorClock, &physics::Clock::update, &waterControl, &WaterControl::controlMoistureLevels);
    QObject::connect(&waterControl, &WaterControl::mainValveWasClosed,  &window, &MainWindow::toggleMainValveToggleButtonOff);
    // Update the enviroment
    QObject::connect(&sensorClock, &physics::Clock::update, &mockEnviroment, &MockEnvironment::generateNewSoilMoistureAndFlow);
    QObject::connect(&sensorClock, &physics::Clock::update, &mockEnviroment, &MockEnvironment::generateNewTemperature);
    QObject::connect(&sensorClock, &physics::Clock::update, &mockEnviroment, &MockEnvironment::generateNewHumidity);

    sensorClock.start();
    notificationClock.start();

    return app.exec();
}

