#ifndef PLANT_H
#define PLANT_H

#include <string>
#include <memory>
#include <chrono>
#include <QDebug>
#include <QDateTime>
#include "plant_profile.h"
#include "control/sensor.h"
#include "control/water_valve.h"

class Plant {
    // Specify the place of the plant in the plant grid
    int plant_grid_row_number_;
    int plant_grid_column_number_;

    std::chrono::system_clock::time_point  sowing_date_;
    std::shared_ptr<PlantProfile> profile_;
    std::shared_ptr<SoilMoistureSensor> soil_moisture_sensor_;

    std::shared_ptr<WaterValve> water_valve_;
public:
    Plant(const std::chrono::system_clock::time_point&  sowing_date, std::shared_ptr<PlantProfile> profile, int row_number = 0, int column_number = 0) :
        plant_grid_row_number_(row_number), plant_grid_column_number_(column_number), sowing_date_(sowing_date), profile_(profile) {}

    bool savePlantToFile(const std::string&);
    void setWaterValve(std::shared_ptr<WaterValve> water_valve) {water_valve_ = water_valve;}
    void setSoilMoistureSensor(std::shared_ptr<SoilMoistureSensor> soil_moisture_sensor) {soil_moisture_sensor_ = soil_moisture_sensor;};
    void setGridPosition(int, int);
    int getGridRowNumber() {return plant_grid_row_number_;}
    int getGridColumnNumber() {return plant_grid_column_number_;}
    std::shared_ptr<WaterValve> getWaterValve() {return water_valve_;}
    std::shared_ptr<PlantProfile> getProfile() {return profile_;}
    std::shared_ptr<SoilMoistureSensor> getSoilMoistureSensor() {return soil_moisture_sensor_;}
    std::shared_ptr<PlantProfile> getPlantProfile() {return profile_;}
    std::chrono::system_clock::time_point  getSowingDate() {return sowing_date_;}
    friend QDebug operator<<(QDebug qdebug, const Plant &pl);
};

#endif // PLANT_H
