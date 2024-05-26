#include "ui/plant_label.h"

void PlantLabel::setPlantLabelLayout() {
    setFrameStyle(QFrame::Box | QFrame::Raised);
    setAlignment(Qt::AlignCenter);
    setStyleSheet("border-radius: 5px; margin-top: 1ex;");
}


void PlantLabel::updatePlantLabel(bool main_valve_is_open, bool water_flow_detected) {
    // Test if the Moisture Sensor is a nullptr
    if(moisture_sensor_) {
        float soil_moisture = moisture_sensor_->getMeasurement();
        QString plant_string = QString("Pflanze %1:\n%2%").arg(property("plant_name").toString(), QString::number(soil_moisture, 'f', 1));
        setText(plant_string);
    }
    // if WaterWalve is no nullptr
    if(water_valve_) {
        // make the background blue if the plant is watered
        if(water_valve_->getValveIsOpen() && main_valve_is_open && water_flow_detected) {
            setStyleSheet("QLabel { background-color : #ADD8E6; color : black; border: 1px solid #40b5db; border-radius: 5px; margin-top: 1ex;}"); // turn blue
        } else if ((water_valve_->getValveIsOpen() && !main_valve_is_open) || (water_valve_->getValveIsOpen() && !water_flow_detected)) {
             setStyleSheet("QLabel { background-color : #EB6734; color : black; border: 1px solid #a1110a; border-radius: 5px; margin-top: 1ex;}"); // turn orange
        } else {
            setStyleSheet("QLabel { background-color : #4ddb4d; color : black; border: 1px solid #0d8c0d; border-radius: 5px; margin-top: 1ex;}"); // Sets it green
        }
    }
}







