#ifndef PLANT_H
#define PLANT_H

#include <string>
#include <memory>
#include <QDebug>
#include <QDateTime>
#include "plant_profile.h"
#include "control/sensor.h"

class Plant {
    // Specify the place of the plant in the plant grid
    int plant_grid_row_number_;
    int plant_grid_column_number_;

    QDateTime  sowing_date;
    std::shared_ptr<PlantProfile> profile;
    std::shared_ptr<SoilMoistureSensor> soil_moisture_sensor_;
public:
    Plant(const QDateTime&  sowing_date, std::shared_ptr<PlantProfile> profile, int row_number = 0, int column_number = 0) :
        plant_grid_row_number_(row_number), plant_grid_column_number_(column_number), sowing_date(sowing_date), profile(profile) {}

    bool savePlantToFile(const std::string&);
    void setSoilMoistureSensor(std::shared_ptr<SoilMoistureSensor> soil_moisture_sensor) {soil_moisture_sensor_ = soil_moisture_sensor;};
    void setGridPosition(int, int);
    int getGridRowNumber() {return plant_grid_row_number_;};
    int getGridColumnNumber() {return plant_grid_column_number_;};
    std::shared_ptr<SoilMoistureSensor> getSoilMoistureSensor() {return soil_moisture_sensor_;};
    std::shared_ptr<PlantProfile> getPlantProfile();
   // void addPlantProfile(std::shared_ptr<PlantProfile>);
    friend QDebug operator<<(QDebug qdebug, const Plant &pl);
};

#endif // PLANT_H
