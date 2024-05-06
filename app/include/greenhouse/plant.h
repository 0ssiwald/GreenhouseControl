#ifndef PLANT_H
#define PLANT_H

#include <string>
//#include <chrono>
#include <memory>
#include <QDebug>
#include <QDateTime>
#include "plant_profile.h"

class Plant {
    QDateTime  sowing_date;
    std::shared_ptr<PlantProfile> profile;
public:
    Plant(const QDateTime&  sowing_date, std::shared_ptr<PlantProfile> profile) :
        sowing_date(sowing_date), profile(profile) {}

    bool savePlantToFile(const std::string&);
    std::shared_ptr<PlantProfile> getPlantProfile();
   // void addPlantProfile(std::shared_ptr<PlantProfile>);
    friend QDebug operator<<(QDebug qdebug, const Plant &pl);
};

#endif // PLANT_H
