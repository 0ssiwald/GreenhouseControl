#include "control/mock_enviroment.h"

#include <cstdlib>
#include <ctime>

float MockEnvironment::getRandomChange(const float min_change, const float max_change) {
    // Seed the random number generator with the current time
    static bool seeded = false;
    if (!seeded) {
        std::srand(std::time(nullptr));
        seeded = true;
    }
    // Generate a random value between kMinChange and kMaxChange
    float randomChange = min_change + static_cast<float>(std::rand()) / (static_cast<float>(RAND_MAX / (max_change - min_change)));
    return randomChange;
}

void MockEnvironment::generateNewTemperature() {
    float temperature = sensor_control_->getTemperatureSensor()->getMeasurement();
    float new_temperature = temperature + getRandomChange();
    sensor_control_->getTemperatureSensor()->setMeasurent(new_temperature);
}
void MockEnvironment::generateNewHumidity() {
    float humidity = sensor_control_->getHumiditySensor()->getMeasurement();
    float new_humidity = humidity + getRandomChange();
    sensor_control_->getHumiditySensor()->setMeasurent(new_humidity);
}

void MockEnvironment::generateNewSoilMoistureAndFlow() {
    // set the flow sensor to 0
    bool flow_detected = false;
    for(auto& group: greenhouse_->getPlantGroups()) {
        for(auto& plant: group->getPlants()) {
            float soil_moisture = plant->getSoilMoistureSensor()->getMeasurement();
            float new_soil_moisture;
            // Water Valve and Main Valve have to be open to raise the soil moisture
            if(plant->getWaterValve()->getValveIsOpen() && water_control_->isMainValveOpen()) {
                new_soil_moisture = soil_moisture + getRandomChange(1.0, 3.0);
                // Turn the flow sensor on
                water_control_->getFlowSensor()->setMeasurent(5.0);
                flow_detected = true;
            } else {
                new_soil_moisture = soil_moisture - getRandomChange(0, 1.0);
            }
            plant->getSoilMoistureSensor()->setMeasurent(new_soil_moisture);
        }
    }
    if(!flow_detected) {
        water_control_->getFlowSensor()->setMeasurent(0.0);
    }
}

