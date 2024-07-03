#ifndef SENSOR_CONTROL_H
#define SENSOR_CONTROL_H

#include <QObject>
#include "sensors_actors/sensor.h"
#include "greenhouse/greenhouse.h"


class SensorControl: public QObject {
    Q_OBJECT
    Sensor* temperature_sensor_;
    Sensor* humidity_sensor_;
    Greenhouse* greenhouse_;
public:
    explicit SensorControl(Sensor* temperature_sensor, Sensor* humidity_sensor, Greenhouse* greenhouse)
        : QObject(nullptr), temperature_sensor_(temperature_sensor), humidity_sensor_(humidity_sensor), greenhouse_(greenhouse) {}
    SensorControl() = default;
    virtual Sensor* getTemperatureSensor();
    virtual Sensor* getHumiditySensor();
public slots:
    void measureTemperature();
    void measureHumidity();
    void measureSoilMoistures();

signals:
    void temperatureMeasured(float temperature);
    void humidityMeasured(float humidity);
    void soilMoisturesMeasured();
    void updateSoilMoisture(Plant*);

};

#endif // SENSOR_CONTROL_H
