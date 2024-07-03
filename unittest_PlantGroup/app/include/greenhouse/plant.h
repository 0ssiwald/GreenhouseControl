#ifndef PLANT_H
#define PLANT_H

#include <string>
#include <chrono>
#include <QDebug>
#include <QDateTime>
#include "plant_profile.h"
#include "sensors_actors/sensor.h"
#include "sensors_actors/water_valve.h"

class Plant {
    std::string plant_name_;
    // Specify the place of the plant in the plant grid
    unsigned int plant_grid_row_number_;
    unsigned int plant_grid_column_number_;

    std::chrono::system_clock::time_point  sowing_date_;
    PlantProfile* profile_;
    Sensor* soil_sensor_ = nullptr;
    WaterValve* valve_ = nullptr;
public:
    Plant(const std::string & name, const std::chrono::system_clock::time_point&  sowing_date, PlantProfile* profile, unsigned int row_number = 0,unsigned int column_number = 0) :
        plant_name_(name), plant_grid_row_number_(row_number), plant_grid_column_number_(column_number), sowing_date_(sowing_date), profile_(profile) {}
    // For Mock classes for testing
    Plant() = default;
    virtual ~Plant() = default;

    void setGridPosition(unsigned int,unsigned int);
    unsigned int getGridRowNumber();
    unsigned int getGridColumnNumber();
    virtual Sensor* getSoilSensor() {return soil_sensor_;}
    virtual WaterValve* getWaterValve() {return valve_;}
    void setSoilSensor(Sensor* soilsensor) {soil_sensor_ = soilsensor;}
    void setWaterValve(WaterValve* valve) {valve_ = valve;}
    virtual std::string getPlantName() {return plant_name_;}
    virtual PlantProfile* getPlantProfile() {return profile_;}
    std::chrono::system_clock::time_point  getSowingDate() {return sowing_date_;}
};

#endif // PLANT_H
