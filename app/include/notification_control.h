#ifndef NOTIFICATION_CONTROL_H
#define NOTIFICATION_CONTROL_H
#include <QObject>
#include <QDateTime>
#include <QtDebug>
#include "notification.h"
#include "greenhouse/greenhouse.h"

class NotificationControl: public QObject {
    Q_OBJECT
    std::vector<std::shared_ptr<Notification>> active_notification_list_;
    std::shared_ptr<Greenhouse> greenhouse_;
public:
    explicit NotificationControl(std::shared_ptr<Greenhouse>);
    void addNotification(NotificationTypes, QDateTime);
    std::vector<std::shared_ptr<Notification>> getNotificationList() {return active_notification_list_;}
    bool addNewNotificationToActiveList(int, int, int, QString, NotificationTypes);
    void displayNotifications();
    bool saveNotificationToLog();
    void deleteNotification(int);
public slots:
    void updateNotificationList();
signals:
    void updateNotificationListInUi();
};

#endif // NOTIFICATION_CONTROL_H
