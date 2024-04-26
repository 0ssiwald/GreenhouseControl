#include "notification.h"

void NotificationControl::addNotification(NotificationTypes type, std::chrono::system_clock::time_point date) {
    std::shared_ptr<NotificationHandler> handler;

    switch (type) {
    case NotificationTypes::LampDistanceNotification:
        handler = std::shared_ptr<LampDistanceNotificationHandler>();
        break;
    case NotificationTypes::LampIntensityNotification:
        handler = std::shared_ptr<LampIntensityNotificationHandler>();
        break;
    default:
        //Implement default
        break;
    }
    notification_list.push_back(std::shared_ptr<Notification>(new Notification(date, handler)));
    return;
}


