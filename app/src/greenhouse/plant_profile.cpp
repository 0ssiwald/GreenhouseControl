#include "greenhouse/plant_profile.h"

void PlantProfile::addWeeklyCondition(std::shared_ptr<Condition> condition) {
    conditions_weekly_.push_back(condition);
    return;
}


