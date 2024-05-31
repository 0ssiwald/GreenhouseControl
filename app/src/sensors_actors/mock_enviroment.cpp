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


void MockEnvironment::generateNewSoilMoisture(std::shared_ptr<Plant> plant) {
    for(auto &plant_and_valve: water_control_->getWaterValves()) {
        if(plant == plant_and_valve.first) {
            float soil_moisture = sensor_control_->getSoilSensors()[plant]->getMeasurement();
            float new_soil_moisture;
                if(plant_and_valve.second->getValveIsOpen() && water_control_->isMainValveOpen()) {
                    new_soil_moisture = soil_moisture + getRandomChange(1.0, 3.0);
                } else {
                    new_soil_moisture = soil_moisture - getRandomChange(0, 1.0);
                }
                sensor_control_->getSoilSensors()[plant]->setMeasurent(new_soil_moisture);
            }
        }
}

void MockEnvironment::generateNewFlow( std::shared_ptr<WaterValve> valve) {
    float previous_measurement = water_control_->getFlowSensor()->getMeasurement();
    if(!water_control_->isMainValveOpen()) {
        water_control_->getFlowSensor()->setMeasurent(0.0);
    } else if(valve->getValveIsOpen() ) {
        water_control_->getFlowSensor()->setMeasurent(previous_measurement + 3.0);
    } else if(!valve->getValveIsOpen()) {
        water_control_->getFlowSensor()->setMeasurent(previous_measurement - 3.0);
    }
}
