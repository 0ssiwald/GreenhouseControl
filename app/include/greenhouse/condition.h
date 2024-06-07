#ifndef CONDITION_H
#define CONDITION_H

#include <string>
#include <vector>

class Fertilizer {
    std::string name_;
    std::string type_;
public:
    Fertilizer(const std::string& name, const std::string& type)
        : name_(name), type_(type) {}
    std::string getName() {return name_;}
    std::string getType() {return type_;}
};

struct FertilizerWithAmount {
    Fertilizer* fertilizer_;
    int amount_in_ml_;

    FertilizerWithAmount(Fertilizer* fertilizer, int amount)
        : fertilizer_(fertilizer), amount_in_ml_(amount) {}
    int getAmount() {return amount_in_ml_;}
    Fertilizer* getFertilizer() {return fertilizer_;}
};

class Condition {
    float humidity_;
    float temperature_;
    int lamp_distance_in_cm_;
    std::vector<FertilizerWithAmount> fertilizers_;
public:
    Condition(float humidity, float temperature, int lamp_distance)
        : humidity_(humidity), temperature_(temperature), lamp_distance_in_cm_(lamp_distance) {}
    void addFertilizer(Fertilizer*, int);
    float getHumidity() {return humidity_;}
    float getTemperature() {return temperature_;}
    int getLampDistance() {return lamp_distance_in_cm_;}
    std::vector<FertilizerWithAmount> getFertilizers() {return fertilizers_;}
    std::string getFertilazersAsString();
};


#endif // CONDITION_H
