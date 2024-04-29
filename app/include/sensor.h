#ifndef SENSOR_H
#define SENSOR_H

#include <vector>
#include <string>
#include <memory>
#include <QObject>
#include "log.h"

class MockEnvironment;

class Sensor {
public:
    // virtual destuctor to enshure that derived classes get destroyed
    virtual ~Sensor() = default;
    // must be overritten by derived classes
    virtual float getMeasurement() = 0;
    virtual bool calibrate() = 0;
};

class SoilMoistureSensor: public Sensor {
    float dry_calibration_value;
    float wet_calibration_value;
public:
    void loadCalibration(std::string file_name="calibration.csv");
    virtual bool calibrate() override {
        throw("Not implemented");
    }
    virtual float getMeasurement() override {
        throw("Not implemented");
    }
};

class TemperatureSensor: public Sensor {
    virtual bool calibrate() override {
        throw("Not implemented");
    }
    virtual float getMeasurement() override {
        throw("Not implemented");
    }
};
class HumiditySensor: public Sensor {
    virtual bool calibrate() override {
        throw("Not implemented");
    }
    virtual float getMeasurement() override {
        throw("Not implemented");
    }
};
class FlowSensor: public Sensor {
    virtual bool calibrate() override {
        throw("Not implemented");
    }
    virtual float getMeasurement() override {
        throw("Not implemented");
    }
    // signal FlowSignal() ?????
};


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
    void addMockSensors(MockEnvironment&);
    int getSecondsperMeasurement() const {return seconds_per_measurement_;};
public slots:
    void measureTemperature();
    void measureHumidity();
    //void measureSoilMoistures();

signals:
    void temperatureMeasured(float temperature);
    void humidityMeasured(float humidity);

};


#endif // SENSOR_H
