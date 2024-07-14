#include "sensors_actors/mock_environment.h"
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
    float new_temperature = temperature + getRandomChange(-0.5, 0.5);
    sensor_control_->getTemperatureSensor()->setMeasurent(new_temperature);
}

void MockEnvironment::generateNewHumidity() {
    float humidity = sensor_control_->getHumiditySensor()->getMeasurement();
    float new_humidity = humidity + getRandomChange(-1.0, 1.0);
    sensor_control_->getHumiditySensor()->setMeasurent(new_humidity);
}

void MockEnvironment::generateNewSoilMoisture(Plant* plant) {
    float soil_moisture = plant->getSoilSensor()->getMeasurement();
    float new_soil_moisture;
    // If the plant is in the watering process soil moisture is increased else its decreased to simulate drying
    if(plant->getWaterValve()->getValveIsOpen() && water_control_->isMainValveOpen() && water_control_->getFlowSensor()->isFlowDetected()) {
        new_soil_moisture = soil_moisture + getRandomChange(1.0, 3.0);
    } else {
        new_soil_moisture = soil_moisture - getRandomChange(0, 1.0);
    }
    plant->getSoilSensor()->setMeasurent(new_soil_moisture);
}

void MockEnvironment::generateNewFlow(WaterValve* valve) {
    int water_amount_per_open_valve = 3.0;
    float previous_measurement = water_control_->getFlowSensor()->getMeasurement();
    if(!water_control_->isMainValveOpen()) {
        water_control_->getFlowSensor()->setMeasurent(0.0);
    // Sets the Flow to the appropriate number for the number of open valves (if main valve was changed the flow is reseted)
    } else if (valve == water_control_->getMainValve()){
        water_control_->getFlowSensor()->setMeasurent(water_amount_per_open_valve * water_control_->getNumberOfOpenValves());
    } else if(valve->getValveIsOpen() ) {
        water_control_->getFlowSensor()->setMeasurent(previous_measurement + water_amount_per_open_valve);
    } else if(!valve->getValveIsOpen()) {
        water_control_->getFlowSensor()->setMeasurent(previous_measurement - water_amount_per_open_valve);
    }
}

