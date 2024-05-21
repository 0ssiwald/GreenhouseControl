#include "control/water_control.h"

WaterControl::WaterControl(std::shared_ptr<Greenhouse> greenhouse)
    : QObject(nullptr), greenhouse_(greenhouse) {
    number_of_open_valves_ = 0;
    //createMainValve
    main_valve_ = std::make_shared<WaterValve>();
    openMainValve();
    //createFlowSensor
    flow_sensor_ = std::make_shared<FlowSensor>();
    addWaterValvesToPlants();
}

void WaterControl::controlMoistureLevels() {
    for(size_t group_index = 0;group_index < greenhouse_->getPlantGroups().size(); group_index++) {
        for(size_t plant_index = 0; plant_index < greenhouse_->getPlantGroups()[group_index]->getPlants().size(); plant_index++) {
            std::shared_ptr<Plant> plant = greenhouse_->getPlantGroups()[group_index]->getPlants()[plant_index];
            float soil_moisture = plant->getSoilMoistureSensor()->getMeasurement();
            if(soil_moisture < plant->getPlantProfile()->getLowerWateringThreshold() && !plant->getWaterValve()->getValveIsOpen()) {
                plant->getWaterValve()->openValve();
                number_of_open_valves_++;
                qInfo().noquote() << QString("Watervalve of Plant %1 from Group %2 was opened").arg(QString::number(plant_index + 1), QString::number(group_index + 1));
            }
            if(soil_moisture > plant->getPlantProfile()->getUpperWateringThreshold() && plant->getWaterValve()->getValveIsOpen()) {
                plant->getWaterValve()->closeValve();
                number_of_open_valves_--;
                qInfo().noquote() << QString("Watervalve of Plant %1 from Group %2 was closed").arg(QString::number(plant_index + 1), QString::number(group_index + 1));
            }
        }
    }
    controlUnregularFlow();
}


// Test if a flow is detected when all valves should be off
void WaterControl::controlUnregularFlow() {
    if(flow_sensor_->isFlowDetected() && number_of_open_valves_ <= 0) {
        qCritical().noquote() << "Unreagular water flow detected. Main Valve gets closed";
        closeMainValve();
        emit mainValveWasClosed();
    }
}


void WaterControl::addWaterValvesToPlants() {
    for(auto& group_iterator: greenhouse_->getPlantGroups()) {
        for(auto& plant_iterator: group_iterator->getPlants()) {
            std::shared_ptr<WaterValve> water_valve = std::make_shared<WaterValve>();
            plant_iterator->setWaterValve(water_valve);
        }
    }
}
