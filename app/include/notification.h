#ifndef NOTIFICATION_H
#define NOTIFICATION_H

#include <string>
#include <vector>
#include <chrono>

enum class NotificationTypes {
    LampDistanceNotification,
    FertilizerNotification,
    TemperatureNotification,
    HumidityNotification,
};

class Notification {
    std::chrono::system_clock::time_point activation_timepoint_;
    int week_index_;
    std::string group_name_;
    // Vector because multible plants can have the same notification
    std::vector<std::string> plant_names_;
    std::string value_as_string_;
    NotificationTypes notification_type_;

public:
    Notification(std::chrono::system_clock::time_point time_point,int week_index,std::string group_name,
                 std::string plant_name, std::string value_as_string, NotificationTypes notification_type)
        : activation_timepoint_(time_point), week_index_(week_index), group_name_(group_name),
        value_as_string_(value_as_string), notification_type_(notification_type){
        plant_names_.push_back(plant_name);
    }

    std::chrono::system_clock::time_point getActivationTimepoint() {return activation_timepoint_;}
    void addPlant(std::string plant_name) {plant_names_.push_back(plant_name);}
    bool isNotificationTheSameForAnotherPlant(std::chrono::system_clock::time_point,int, std::string, std::string, NotificationTypes);
    std::string getNotificationMessage();
};

#endif // NOTIFICATION_H
