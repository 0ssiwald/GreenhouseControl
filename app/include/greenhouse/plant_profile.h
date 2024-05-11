#ifndef PLANT_PROFILE_H
#define PLANT_PROFILE_H

#include <string>
#include <vector>
#include <memory>
#include <QString>


class Fertilizer {
    QString name_;
    QString type_;
public:
    Fertilizer(const QString& name, const QString& type)
        : name_(name), type_(type) {}
    QString getName() {return name_;}
    QString getType() {return type_;}
};

struct FertilizerWithAmount {
    std::shared_ptr<Fertilizer> fertilizer_;
    int amount_in_ml_;

    FertilizerWithAmount(std::shared_ptr<Fertilizer> fertilizer, int amount)
        : fertilizer_(fertilizer), amount_in_ml_(amount) {}
    int getAmount() {return amount_in_ml_;}
    std::shared_ptr<Fertilizer> getFertilizer() {return fertilizer_;}

};

class Condition {
    int number_of_week_;
    float humidity_;
    float temperature_;
    int lamp_distance_in_cm_;
    std::vector<FertilizerWithAmount> fertilizers_;
public:
    Condition(int number_of_week, float humidity, float temperature, int lamp_distance)
        : number_of_week_(number_of_week), humidity_(humidity), temperature_(temperature), lamp_distance_in_cm_(lamp_distance) {}
    void addFertilizer(std::shared_ptr<Fertilizer>, int);
    int getNumberOfWeek() {return number_of_week_;}
    float getHumidity() {return humidity_;}
    float getTemperature() {return temperature_;}
    int getLampDistance() {return lamp_distance_in_cm_;}
    std::vector<FertilizerWithAmount> getFertilizers() {return fertilizers_;}
};

class WateringProfile {
protected:
    int watering_threshold_;
    int watering_duration_in_s_;
public:
    WateringProfile(int threshold = 30, int duration = 30)
        : watering_threshold_(threshold), watering_duration_in_s_(duration) {}
    int getWateringThreshold() const;
    int getWateringDuration() const;
};

class PlantProfile: public WateringProfile {
    QString strain_name_;
    int length_vegitation_period_;
    int length_flowering_period_;
    float expected_thc_content_;
    float expected_cbd_content_;
    QString soil_type_;
    std::vector<std::shared_ptr<Condition>> conditions_weekly_;
public:
    //call by reference can improve the overall performance and memory usage e.g. const std::string&
    PlantProfile(const QString& strain_name, int length_vegitation_period, int length_flowering_period,
                 float expected_thc_content, float expected_cbd_content, const QString& soil_type,
                 int watering_threshold, int watering_duration_in_s) :
        WateringProfile(watering_threshold, watering_duration_in_s),
        strain_name_(strain_name), length_vegitation_period_(length_vegitation_period),
        length_flowering_period_(length_flowering_period), expected_thc_content_(expected_thc_content),
        expected_cbd_content_(expected_cbd_content), soil_type_(soil_type) {}

    QString& getStrainName() {return strain_name_;}
    int getLengthVegitationPeriod() {return length_vegitation_period_;}
    int getLengthFloweringPeriod() {return length_flowering_period_;}
    float getExpectedThcContent() {return expected_thc_content_;}
    float getExpectedCbdContent() {return expected_cbd_content_;}
    QString& getSoilType() {return soil_type_;}
    std::vector<std::shared_ptr<Condition>> getConditionsWeekly() {return conditions_weekly_;}

    bool savePlantProfileToFile(const std::string& file_name);
    void addWeeklyCondition(std::shared_ptr<Condition>);
};

#endif // PLANT_PROFILE_H
