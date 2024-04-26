#ifndef SENSOR_H
#define SENSOR_H

#include <vector>
#include <string>
#include <memory>

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


class SensorControl {
    int measurements_per_minute_;
    std::vector<std::shared_ptr<Sensor>> soil_sensors_;
    std::shared_ptr<Sensor> temperature_sensor_;
    std::shared_ptr<Sensor> humidity_sensor_;
    std::shared_ptr<SystemLog> system_log_;
public:
    SensorControl(int measurements_per_minute = 1)
        : measurements_per_minute_(measurements_per_minute) {}
    float measureTemperature();
    float measureHumidity();
    float measureSoilMoistures();
    void setLog();
    void addSoilSensor(std::shared_ptr<Sensor>);
    void addMockSensors(MockEnvironment&);
};


#endif // SENSOR_H
