#ifndef NOTIFICATION_H
#define NOTIFICATION_H

#include <chrono>
#include <vector>
#include <memory>
#include "log.h"
#include "greenhouse.h"

enum class NotificationTypes {
    LampDistanceNotification,
    LampIntensityNotification,
    FertilizerNotification,
    TemperatureNotification,
    HumidityNotification,
    HarvestNotification
};


class NotificationHandler {
public:
    virtual ~NotificationHandler() = default;
    virtual std::string getNotificationMessage() const = 0;
};

class LampDistanceNotificationHandler : public NotificationHandler {
public:
    std::string getNotificationMessage() const override {
        return "Lamp distance should be adjusted.";
    }
};

class LampIntensityNotificationHandler : public NotificationHandler {
public:
    std::string getNotificationMessage() const override {
        return "Lamp intensity should be adjusted.";
    }
};

class Notification {
    std::chrono::system_clock::time_point notification_date;
    std::shared_ptr<NotificationHandler> notification_handler;

public:
    Notification(std::chrono::system_clock::time_point date, std::shared_ptr<NotificationHandler> handler)
        : notification_date(date), notification_handler(handler) {}

    std::string getNotificationMessage() const {
        return notification_handler->getNotificationMessage();
    }
};

class NotificationControl {
    int time_between_checks_in_s;
    std::vector<std::shared_ptr<Notification>> notification_list;
    std::shared_ptr<SystemLog> system_log;
    std::shared_ptr<Greenhouse> greenhouse;
public:
    void updateNotificationList();
    void addNotification(NotificationTypes, std::chrono::system_clock::time_point);
    std::shared_ptr<Notification> checkNotificationDeadlines();
    void displayNotification();
    bool saveNotificationToLog();
};


/*
enum NotificationTypes {LampDistanceNotification, LampIntensityNotification, FertilizerNotification, TemperatureNotification, HumidityNotification, HarvestNotification};

class Notification {
    std::chrono::system_clock::time_point notification_date;
    NotificationTypes notification_type;
};

class NotificationControl {
    int time_between_checks_in_s;
    std::vector<std::shared_ptr<Notification>> notification_list;
    std::shared_ptr<SystemLog> system_log;
    std::shared_ptr<Greenhouse> greenhouse;
public:
    void updateNotificationList();
    std::shared_ptr<Notification> checkNotificationDeadlines();
    void displaNotification();
    bool saveNotificationToLog();
};
*/
#endif // NOTIFICATION_H
