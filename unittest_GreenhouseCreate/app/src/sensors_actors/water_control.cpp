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

void WaterControl::controlMoistureLevels() {
    for(auto& plant: greenhouse_->getAllPlants()) {
        float soil_moisture = plant->getSoilSensor()->getMeasurement();
        if(soil_moisture < plant->getPlantProfile()->getLowerWateringThreshold() && !plant->getWaterValve()->getValveIsOpen()) {
            plant->getWaterValve()->openValve();
            number_of_open_valves_++;
            qInfo().noquote() << QString("Watervalve of Plant %1 was opened").arg(QString::fromStdString(plant->getPlantName()));
            emit updateFlow(plant->getWaterValve());
        }
        if(soil_moisture > plant->getPlantProfile()->getUpperWateringThreshold() && plant->getWaterValve()->getValveIsOpen()) {
            plant->getWaterValve()->closeValve();
            number_of_open_valves_--;
            qInfo().noquote() << QString("Watervalve of Plant %1 was closed").arg(QString::fromStdString(plant->getPlantName()));
            emit updateFlow(plant->getWaterValve());
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


