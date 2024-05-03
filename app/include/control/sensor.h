#ifndef SENSOR_H
#define SENSOR_H

#include <string>
#include <QObject>
#include "mock_enviroment.h"

class Sensor {
protected:
    MockEnvironment &mock_enviroment_;
public:
    Sensor(MockEnvironment &mock_env)
        : mock_enviroment_(mock_env) {}
    // virtual destuctor to enshure that derived classes get destroyed
    virtual ~Sensor() = default;
    // must be overritten by derived classes
    virtual float getMeasurement() = 0;
    virtual bool calibrate() = 0;
};

class SoilMoistureSensor: public Sensor {
    float dry_calibration_value_;
    float wet_calibration_value_;
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
public:
    TemperatureSensor(MockEnvironment &mock_env)
        : Sensor(mock_env) {}
    virtual bool calibrate() override {
        throw("Not implemented");
    }
    virtual float getMeasurement() override {
    return mock_enviroment_.generateNewHumidity();
    }
};
class HumiditySensor: public Sensor {
public:
    HumiditySensor(MockEnvironment &mock_env)
        : Sensor(mock_env) {}
    virtual bool calibrate() override {
        throw("Not implemented");
    }
    virtual float getMeasurement() override {
        return mock_enviroment_.generateNewTemperature();
    }
};
class FlowSensor: public Sensor {
public:
    virtual bool calibrate() override {
        throw("Not implemented");
    }
    virtual float getMeasurement() override {
        throw("Not implemented");
    }
    // signal FlowSignal() ?????
};

#endif // SENSOR_H
