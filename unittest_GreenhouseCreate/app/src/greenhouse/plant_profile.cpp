#include "greenhouse/plant_profile.h"

PlantProfile::PlantProfile(PlantProfileAttributes attributes) {
    expected_cbd_content_ = attributes.expected_cbd_content_;
    expected_thc_content_ = attributes.expected_thc_content_;
    length_flowering_period_ = attributes.length_flowering_period_;
    length_vegitation_period_ = attributes.length_vegitation_period_;
    lower_watering_threshold_ = attributes.lower_watering_threshold_;
    upper_watering_threshold_ = attributes.upper_watering_threshold_;
    soil_type_ = attributes.soil_type_;
    strain_name_ = attributes.strain_name_;
}

