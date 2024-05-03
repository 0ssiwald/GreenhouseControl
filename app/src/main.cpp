#include "greenhouse/greenhouse.h"
#include "ui/mainwindow.h"
#include "control/mock_enviroment.h"
#include "clock.h"
#include "log.h"
#include "control/sensor_control.h"

#include <QApplication>
#include <QSettings>
#include <QCommandLineParser>
#include <QtDebug>
#include <QDir>
#include <QObject>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    // Create Greenhouse
    GreenhouseCreate ghc;
    std::shared_ptr<Greenhouse> greenhouse = ghc.createGreenhouseFromCode();
    qDebug() << *greenhouse;

    //Create Log
    std::shared_ptr<SystemLog> log = std::make_shared<SystemLog>("../../../../app/data/log.csv");
    log->loadLogMessagesFromFile();

    // Init GUI
    // Besser nicht dem Constructor übergeben sondern mit set Functions?????????
    MainWindow window(greenhouse, log);
    window.show();

    // Create a mock environment
    MockEnvironment mockEnv(25.0, 60.0, 40.0);
    int seconds_per_measurement = 2;

    SensorControl sensorControl(seconds_per_measurement);
    sensorControl.addSystemLog(log);
    // Add mock sensors to the SensorControl
    sensorControl.addSensors(mockEnv);

    // Init Physics
    physics::Clock clock(sensorControl.getSecondsperMeasurement());
    QObject::connect(&clock, &physics::Clock::update, &sensorControl, &SensorControl::measureTemperature);
    // Connect the signal from the SensorControl class to the updateTemperatureLabel slot in the MainWindow class
    QObject::connect(&sensorControl, &SensorControl::temperatureMeasured, &window, &MainWindow::updateTemperatureLabel);
    // Same for humidity
    QObject::connect(&clock, &physics::Clock::update, &sensorControl, &SensorControl::measureHumidity);
    QObject::connect(&sensorControl, &SensorControl::humidityMeasured, &window, &MainWindow::updateHumidityLabel);

    clock.start();

    return app.exec();
}


/*

#include "circlemotionprovider.h"
#include "clock.h"
#include "rocket.h"
#include "mainwindow.h"

#include <QApplication>
#include <QSettings>
#include <QCommandLineParser>
#include <QtDebug>
#include <QDir>

int main(int argc, char *argv[])
{
    // Set some defaults
    QCoreApplication::setApplicationName("SE 2 Demo");
    QCoreApplication::setApplicationVersion("0.1");
    QCoreApplication::setOrganizationName("Berliner Hochschule für Technik");
    QCoreApplication::setOrganizationDomain("bht-berlin.de");

    qDebug() << QCoreApplication::applicationName() << " v" << QCoreApplication::applicationVersion();
    qDebug() << "Current working directory" << QDir::currentPath();

    // Parse command line options
    QApplication app(argc, argv);
    QCommandLineParser parser;
    parser.setApplicationDescription("A demo application for the SE2 course at Beuth University");
    parser.addHelpOption();
    parser.addVersionOption();
    parser.addOption({{"c", "config"}, "Use file for configuration", "name of file", "default.cfg"});
    parser.process(app);

    // Process config file
    const QString configFile = parser.value("config");
    qDebug() << "Using config file" << configFile;

    // Default values are encoded here and used if not given by config file
    // Note: the file is located using the current working directory - make sure that the file and CWD is in the right spot
    QSettings settings(configFile, QSettings::IniFormat);

    int framerate = settings.value("framerate", 30).toInt();
    float frequency = settings.value("frequency", 0.2).toFloat();
    float amplitude = settings.value("amplitude", 200).toFloat();
    float offset = settings.value("offset", 1.507).toFloat();
    bool clockwise = settings.value("clockwise", false).toBool();

    // Init GUI
    MainWindow window;
    window.show();

    // Init Logic
    logic::RocketImpl rocket(400, 300);
    logic::CircleMotionProvider motion(frequency, amplitude, offset, clockwise);
    motion.setRocket(&rocket);  // dependency injection
    QObject::connect(&rocket, &logic::RocketImpl::rocketMovementUpdate, &window, &MainWindow::moveRocket);

    // Init Physics
    physics::Clock clock(framerate);
    QObject::connect(&clock, &physics::Clock::update, &motion, &logic::CircleMotionProvider::update);

    // Connect GUI button to clock
    QObject::connect(&window, &MainWindow::start, &clock, QOverload<>::of(&physics::Clock::start));
    QObject::connect(&window, &MainWindow::stop, &clock, QOverload<>::of(&physics::Clock::stop));

    // Go!
    return app.exec();
}

*/
