#ifndef PLANT_PROFILE_H
#define PLANT_PROFILE_H

#include <string>
#include <vector>
#include <memory>


class Fertilizer {
    std::string name;
    std::string type;
public:
    Fertilizer(const std::string& name, const std::string& type)
        : name(name), type(type) {}
};

struct FertilizerWithAmount {
    std::shared_ptr<Fertilizer> fertilizer;
    int amount;

    FertilizerWithAmount(std::shared_ptr<Fertilizer> fertilizer, int amount)
        : fertilizer(fertilizer), amount(amount) {}
};

class Condition {
    int number_of_week;
    float humidity;
    float temperature;
    int lamp_distance;
    std::vector<FertilizerWithAmount> fertilizers;
public:
    Condition(int number_of_week, float humidity, float temperature, int lamp_distance)
        : number_of_week(number_of_week), humidity(humidity), temperature(temperature), lamp_distance(lamp_distance) {}
    void addFertilizer(std::shared_ptr<Fertilizer>, int);
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
    std::vector<std::shared_ptr<Condition>> conditions_weekly;
public:
    //call by reference can improve the overall performance and memory usage e.g. const std::string&
    PlantProfile(const std::string& strain_name, int length_vegitation_period, int length_flowering_period,
                 float expected_thc_content, float expected_cbd_content, const std::string& soil_type,
                 int watering_threshold, int watering_duration_in_s) :
        WateringProfile(watering_threshold, watering_duration_in_s),
        strain_name(strain_name), length_vegitation_period(length_vegitation_period),
        length_flowering_period(length_flowering_period), expected_thc_content(expected_thc_content),
        expected_cbd_content(expected_cbd_content), soil_type(soil_type) {}

    bool savePlantProfileToFile(const std::string& file_name);
    std::string displayPlantProfile();
    void addWeeklyCondition(std::shared_ptr<Condition>);
};

#endif // PLANT_PROFILE_H
