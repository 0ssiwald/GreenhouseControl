#ifndef NOTIFICATION_H
#define NOTIFICATION_H

#include <chrono>
#include <vector>
#include "log.h"
#include "greenhouse.h"

enum NotificationTypes {LampDistanceNotification, LampIntensityNotification, FertilizerNotification, TemperatureNotification, HumidityNotification, HarvestNotification};

class Notification {
    std::chrono::system_clock::time_point notification_date;
    NotificationTypes notification_type;
public:
    Notification();
};

class NotificationControl {
    int time_between_checks_in_s;
    std::vector<Notification*> notification_list;
    SystemLog* system_log;
    Greenhouse* greenhouse;
public:
    void updateNotificationList();
    Notification* checkNotificationDeadlines();
    void displaNotification();
    bool saveNotificationToLog();
};

#endif // NOTIFICATION_H
