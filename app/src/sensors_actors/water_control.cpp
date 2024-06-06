#include "sensors_actors/water_control.h"

void WaterControl::openMainValve() {
    main_valve_->openValve();
    // If valve is change the flow is reseted to the unmanipulated vlaue
    emit updateFlow(main_valve_);
}
void WaterControl::closeMainValve() {
    main_valve_->closeValve();
    // If valve is change the flow is reseted to the unmanipulated vlaue
    emit updateFlow(main_valve_);
}

WaterControl::WaterControl(std::vector<std::shared_ptr<Plant>> plants, SensorControl* sensor_control)
    : QObject(nullptr), sensor_control_(sensor_control) {
    //createMainValve
    main_valve_ = std::make_shared<WaterValve>();
    openMainValve();
    //createFlowSensor
    flow_sensor_ = std::make_shared<FlowSensor>();
    addWaterValves(plants);
}

void WaterControl::controlMoistureLevels() {
    for(auto& plant_with_valve: plants_with_water_valves_) {
        for(auto &plant_with_sensor: sensor_control_->getSoilSensors()) {
            if(plant_with_valve.first == plant_with_sensor.first) {
                float soil_moisture = plant_with_sensor.second->getMeasurement();
                if(soil_moisture < plant_with_valve.first->getPlantProfile()->getLowerWateringThreshold() && !plant_with_valve.second->getValveIsOpen()) {
                    plant_with_valve.second->openValve();
                    number_of_open_valves_++;
                    qInfo().noquote() << QString("Watervalve of Plant %1 was opened").arg(QString::fromStdString(plant_with_valve.first->getPlantName()));
                    emit updateFlow(plant_with_valve.second);
                }
                if(soil_moisture > plant_with_valve.first->getPlantProfile()->getUpperWateringThreshold() && plant_with_valve.second->getValveIsOpen()) {
                    plant_with_valve.second->closeValve();
                    number_of_open_valves_--;
                    qInfo().noquote() << QString("Watervalve of Plant %1 was closed").arg(QString::fromStdString(plant_with_valve.first->getPlantName()));
                    emit updateFlow(plant_with_valve.second);
                }
            }
        }
    }
    emit moistureLevelsControled();
    controlUnregularFlow();
}

// Test if a flow is detected when all valves should be off
void WaterControl::controlUnregularFlow() {
    if(flow_sensor_->isFlowDetected() && number_of_open_valves_ == 0) {
        qCritical().noquote() << "Unreagular water flow detected. Main Valve gets closed";
        emit mainValveWasClosed();
        closeMainValve();  
    }
}


void WaterControl::addWaterValves(std::vector<std::shared_ptr<Plant>> plants) {
    for(auto& plant: plants) {
        std::shared_ptr<WaterValve> water_valve = std::make_shared<WaterValve>();
        plants_with_water_valves_.insert_or_assign(plant, water_valve);
    }
}


