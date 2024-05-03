#ifndef SENSOR_CONTROL_H
#define SENSOR_CONTROL_H

#include <vector>
#include <memory>
#include <QObject>

#include "sensor.h"
#include "log.h"
#include "mock_enviroment.h"


class SensorControl: public QObject {
    Q_OBJECT
    int seconds_per_measurement_;
    std::vector<std::shared_ptr<Sensor>> soil_sensors_;
    std::shared_ptr<Sensor> temperature_sensor_;
    std::shared_ptr<Sensor> humidity_sensor_;
    std::shared_ptr<SystemLog> system_log_;
public:
    explicit SensorControl(int seconds_per_measurement = 1)
        : QObject(nullptr), seconds_per_measurement_(seconds_per_measurement) {}
    //void setLog();
    void addSoilSensor(std::shared_ptr<Sensor>);
    void addSensors(MockEnvironment&);
    void addSystemLog(std::shared_ptr<SystemLog> system_log) {system_log_ = system_log;};
    int getSecondsperMeasurement() const {return seconds_per_measurement_;};
public slots:
    void measureTemperature();
    void measureHumidity();
    //void measureSoilMoistures();

signals:
    void temperatureMeasured(float temperature);
    void humidityMeasured(float humidity);

};

#endif // SENSOR_CONTROL_H
