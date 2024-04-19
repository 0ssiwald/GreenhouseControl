#include "mainwindow.h"
#include "circlemotionprovider.h"
#include "clock.h"
#include "rocket.h"

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
