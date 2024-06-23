#ifndef PLANT_PROFILE_H
#define PLANT_PROFILE_H

#include <vector>
#include <string>
#include "condition.h"

// To have only one parameter for cstructor
struct PlantProfileAttributes {
    std::string strain_name_;
    int length_vegitation_period_;
    int length_flowering_period_;
    float expected_thc_content_;
    float expected_cbd_content_;
    std::string soil_type_;
    int lower_watering_threshold_;
    int upper_watering_threshold_;
};


class WateringProfile {
protected:
    // it gets waterterd from the lower to the upper threshold
    int lower_watering_threshold_;
    int upper_watering_threshold_;
public:
    WateringProfile(int lower_threshold = 30,int upper_threshold = 50)
        : lower_watering_threshold_(lower_threshold), upper_watering_threshold_(upper_threshold) {}

    virtual ~WateringProfile() = default;

    virtual int getLowerWateringThreshold() {return lower_watering_threshold_;}
    virtual int getUpperWateringThreshold() {return upper_watering_threshold_;}

};

class PlantProfile: public WateringProfile {
    std::string strain_name_;
    int length_vegitation_period_;
    int length_flowering_period_;
    float expected_thc_content_;
    float expected_cbd_content_;
    std::string soil_type_;
    std::vector<Condition*> conditions_weekly_;
public:
    PlantProfile(PlantProfileAttributes attributes);

    // For Mock methods for testing
    PlantProfile() = default;
    virtual ~PlantProfile() = default;

    std::string& getStrainName() {return strain_name_;}
    int getLengthVegitationPeriod() {return length_vegitation_period_;}
    int getLengthFloweringPeriod() {return length_flowering_period_;}
    float getExpectedThcContent() {return expected_thc_content_;}
    float getExpectedCbdContent() {return expected_cbd_content_;}
    std::string& getSoilType() {return soil_type_;}
    std::vector<Condition*>& getConditionsWeekly() {return conditions_weekly_;}
    void setWeeklyConditions(std::vector<Condition*> conditions) {conditions_weekly_ = conditions;}
};

#endif // PLANT_PROFILE_H
