#ifndef PLANT_PROFILE_H
#define PLANT_PROFILE_H

#include <string>
#include <vector>

class FertelizerComponents {
    float amount;
    std::string type;
};

class Fertilizer {
    std::string name;
    std::string type;
    std::vector<FertelizerComponents*> components;
public:
    Fertilizer(const std::string& name, const std::string& type)
        : name(name), type(type) {}
};


class ConditionsWeekly {
    int number_of_week;
    float humidity;
    float temperature;
    int lamp_distance;
    std::vector<Fertilizer*> fertilizers;
public:

    ConditionsWeekly(int number_of_week, float humidity, float temperature, int lamp_distance) :
        number_of_week(number_of_week), humidity(humidity), temperature(temperature), lamp_distance(lamp_distance) {}

    ~ConditionsWeekly() {
        for (auto fertilizer : fertilizers) {
            delete fertilizer;
        }
    }
};

class WateringProfile {
protected:
    int watering_threshold;
    int watering_duration_in_s;
public:
    WateringProfile(int threshold = 30, int duration = 30)
        : watering_threshold(threshold), watering_duration_in_s(duration) {}
    int getWateringThreshold();
    int getWateringDuration();
};

class PlantProfile: public WateringProfile {
    std::string strain_name;
    int length_vegitation_period;
    int length_flowering_period;
    float expected_thc_content;
    float expected_cbd_content;
    std::string soil_type;

public:
    std::vector<ConditionsWeekly*> conditions_weekly;
    //call by reference can improve the overall performance and memory usage e.g. const std::string&
    PlantProfile(const std::string& strain_name, int length_vegitation_period, int length_flowering_period,
                 float expected_thc_content, float expected_cbd_content, const std::string& soil_type,
                 int watering_threshold, int watering_duration_in_s) :
        WateringProfile(watering_threshold, watering_duration_in_s),
        strain_name(strain_name), length_vegitation_period(length_vegitation_period),
        length_flowering_period(length_flowering_period), expected_thc_content(expected_thc_content),
        expected_cbd_content(expected_cbd_content), soil_type(soil_type) {}

    ~PlantProfile() {
        for (auto condition : conditions_weekly) {
            delete condition;
        }
    }

    bool savePlantProfileToFile(const std::string& file_name);
    std::string displayPlantProfile();
};

#endif // PLANT_PROFILE_H
