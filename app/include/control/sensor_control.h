#ifndef SENSOR_CONTROL_H
#define SENSOR_CONTROL_H

#include <memory>
#include <QObject>
#include "sensor.h"
#include "greenhouse/greenhouse.h"
#include "mock_enviroment.h"


class SensorControl: public QObject {
    Q_OBJECT
    int seconds_per_measurement_;
    std::shared_ptr<Sensor> temperature_sensor_;
    std::shared_ptr<Greenhouse> greenhouse_;
    std::shared_ptr<Sensor> humidity_sensor_;
    std::shared_ptr<MockEnvironment> mock_enviroment_;
public:
    explicit SensorControl(std::shared_ptr<MockEnvironment>, std::shared_ptr<Greenhouse>, int);

    void addSoilSensorsToPlants();
    int getSecondsperMeasurement() const {return seconds_per_measurement_;};
public slots:
    void measureTemperature();
    void measureHumidity();
    void measureSoilMoistures();

signals:
    void temperatureMeasured(float temperature);
    void humidityMeasured(float humidity);
    void soilMoisturesMeasured();

};

#endif // SENSOR_CONTROL_H
