#ifndef PLANT_PROFILE_H
#define PLANT_PROFILE_H

#include <vector>
#include <string>
#include "condition.h"


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
    //call by reference can improve the overall performance and memory usage e.g. const std::string&
    PlantProfile(const std::string& strain_name, int length_vegitation_period, int length_flowering_period,
                 float expected_thc_content, float expected_cbd_content, const std::string& soil_type,
                 int lower_watering_threshold, int upper_watering_threshold) :
        WateringProfile(lower_watering_threshold, upper_watering_threshold),
        strain_name_(strain_name), length_vegitation_period_(length_vegitation_period),
        length_flowering_period_(length_flowering_period), expected_thc_content_(expected_thc_content),
        expected_cbd_content_(expected_cbd_content), soil_type_(soil_type) {}

    // For Mock methods for testing
    PlantProfile() = default;
    virtual ~PlantProfile() = default;

    std::string& getStrainName() {return strain_name_;}
    int getLengthVegitationPeriod() {return length_vegitation_period_;}
    int getLengthFloweringPeriod() {return length_flowering_period_;}
    float getExpectedThcContent() {return expected_thc_content_;}
    float getExpectedCbdContent() {return expected_cbd_content_;}
    std::string& getSoilType() {return soil_type_;}
    std::vector<Condition*> getConditionsWeekly() {return conditions_weekly_;}

    void addWeeklyCondition(Condition*);
};

#endif // PLANT_PROFILE_H
