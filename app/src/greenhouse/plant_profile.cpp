#include "greenhouse/plant_profile.h"

void Condition::addFertilizer(std::shared_ptr<Fertilizer> fertilizer, int amount) {
    fertilizers.emplace_back(fertilizer, amount);
    return;
}


void PlantProfile::addWeeklyCondition(std::shared_ptr<Condition> condition) {
    conditions_weekly.push_back(condition);
    return;
}
