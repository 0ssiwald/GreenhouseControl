#ifndef NOTIFICATION_CONTROL_H
#define NOTIFICATION_CONTROL_H
#include <QObject>
#include <QDateTime>
#include <QtDebug>
#include <memory>
#include "greenhouse/greenhouse.h"
#include "notification.h"

class NotificationControl: public QObject {
    Q_OBJECT
    std::vector<std::shared_ptr<Notification>> active_notification_list_;
    std::vector<std::shared_ptr<Notification>> impending_notifications_;
public:
    explicit NotificationControl();
    std::vector<std::shared_ptr<Notification>> getActiveNotificationList() {return active_notification_list_;}
    void displayNotifications();
    bool saveNotificationToLog();
    void deleteNotification(int);
    void addNotificationToVector(std::chrono::system_clock::time_point, int, std::string, std::string, std::string, NotificationTypes);
    // mostly for testing
    void createAllNotificationsForAllPlants(std::shared_ptr<Greenhouse>);
    // needs implementation
    void loadNotifications();


public slots:
    void updateActiveNotificationList();
signals:
    void updateNotificationListInUi();
};

#endif // NOTIFICATION_CONTROL_H
