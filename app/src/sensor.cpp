#include "sensor.h"

float Sensor::getValue() const {
    return current_measurement;
}

void SensorControl::addSensor(std::shared_ptr<Sensor> sensor) {
    sensors.push_back(sensor);
}
