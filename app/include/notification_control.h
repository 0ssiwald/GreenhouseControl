#ifndef NOTIFICATION_CONTROL_H
#define NOTIFICATION_CONTROL_H
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QJsonParseError>
#include <QObject>
#include <QtDebug>
#include "greenhouse/greenhouse.h"
#include "notification.h"

class NotificationControl: public QObject {
    Q_OBJECT
    std::vector<Notification*> active_notification_list_;
    std::vector<Notification*> impending_notifications_;
public:
    explicit NotificationControl();
    std::vector<Notification*> getActiveNotificationList() {return active_notification_list_;}
    std::vector<Notification*> getImpendingNotifications() {return impending_notifications_;}
    bool deleteNotification(unsigned int);
    void addNotificationToVector(std::chrono::system_clock::time_point, int, std::string, std::string, std::string, NotificationTypes);
    // mostly for testing because in finished application notifications get loaded from file
    void createAllNotificationsForAllPlants(Greenhouse*);
    bool loadNotificationsFromFile(const std::string&);
    //for unit tests
    void addToActiveNotificationList(Notification* notification) {active_notification_list_.push_back(notification);}
    void addToImpendingNotifications(Notification* notification) {impending_notifications_.push_back(notification);}

public slots:
    void updateActiveNotificationList();
signals:
    void updateNotificationListInUi();
};

#endif // NOTIFICATION_CONTROL_H
