#ifndef CONDITION_H
#define CONDITION_H

#include <QString>
#include <vector>
#include <memory>
#include "notification.h"

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
    float humidity_;
    float temperature_;
    int lamp_distance_in_cm_;
    std::vector<FertilizerWithAmount> fertilizers_;
    std::vector<NotificationTypes> notifications_;
public:
    Condition(float humidity, float temperature, int lamp_distance)
        : humidity_(humidity), temperature_(temperature), lamp_distance_in_cm_(lamp_distance) {}
    void setNotifications(std::vector<NotificationTypes> notifications) {notifications_ = notifications;}
    void removeNotification(NotificationTypes);
    void addFertilizer(std::shared_ptr<Fertilizer>, int);
    std::vector<NotificationTypes> getNotificationTypes() {return notifications_;}
    float getHumidity() {return humidity_;}
    float getTemperature() {return temperature_;}
    int getLampDistance() {return lamp_distance_in_cm_;}
    std::vector<FertilizerWithAmount> getFertilizers() {return fertilizers_;}
    QString getFertilazersAsString();
};


#endif // CONDITION_H
