#ifndef NOTIFICATION_H
#define NOTIFICATION_H

#include <QString>
#include <QDateTime>

enum class NotificationTypes {
    LampDistanceNotification,
    FertilizerNotification,
    TemperatureNotification,
    HumidityNotification,
};

class Notification {
    int group_index_;
    // Vector because multible plants can have the same notification
    int week_index_;
    std::vector<int> plant_indices_;
    QString value_as_string_;
    // Condition ptr;
    NotificationTypes notification_type_;

public:
    Notification(int group_number, int plant_number, int week_number, QString value_as_string, NotificationTypes notification_type)
        : group_index_(group_number), week_index_(week_number), value_as_string_(value_as_string), notification_type_(notification_type) {
        plant_indices_.push_back(plant_number);
    }

    void addPlantNumber(int plant_number) {plant_indices_.push_back(plant_number);}
    int getGroupNumber() {return group_index_;}
    int getWeekNumber() {return week_index_;}
    std::vector<int> getPlantNumbers() {return plant_indices_;}
    QString getValueAsString() {return value_as_string_;}
    NotificationTypes getNotificationType() {return notification_type_;}
    QString getNotificationMessage();
};

#endif // NOTIFICATION_H
