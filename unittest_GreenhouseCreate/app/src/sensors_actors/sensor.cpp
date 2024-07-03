#include "sensors_actors/sensor.h"


float Sensor::getMeasurement() {return measurement_value_;};
void Sensor::setMeasurent(float measurement_value) {measurement_value_ = measurement_value;}

bool FlowSensor::isFlowDetected() {
    if(measurement_value_ > flow_threshold_) {
        return true;
    }
    return false;
}
