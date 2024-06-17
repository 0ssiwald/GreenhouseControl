#include "greenhouse/plant_profile.h"

void PlantProfile::addWeeklyCondition(Condition* condition) {
    conditions_weekly_.push_back(condition);
}
