#include "sensors_actors/water_valve.h"


void WaterValve::openValve() {
    valve_is_open_ = true;
}
void WaterValve::closeValve() {
    valve_is_open_ = false;
}
bool WaterValve::getValveIsOpen() {
    return valve_is_open_;
}
