#include "ui/plant_label.h"

void PlantLabel::setPlantLabelLayout() {
    setFrameStyle(QFrame::Box | QFrame::Raised);
    setAlignment(Qt::AlignCenter);
}


void PlantLabel::updatePlantLabel(bool main_valve_is_open) {
    // Test if the Moisture Sensor is a nullptr
    if(moisture_sensor_) {
        float soil_moisture = moisture_sensor_->getMeasurement();
        QString plant_string = QString("Pflanze %1:\n%2%").arg(QString::number(property("plant_number").toInt()), QString::number(soil_moisture, 'f', 1));
        setText(plant_string);
    }
    // if WaterWalve is no nullptr
    if(water_valve_) {
        // make the background blue if the plant is watered
        if(water_valve_->getValveIsOpen() && main_valve_is_open) {
            setStyleSheet("QLabel { background-color : #ADD8E6; color : black; }");
        } else if (water_valve_->getValveIsOpen() && !main_valve_is_open) {
             setStyleSheet("QLabel { background-color : #EB6734; color : black; }");
        } else {
            setStyleSheet(""); // Sets the style to default
        }
    }
}
