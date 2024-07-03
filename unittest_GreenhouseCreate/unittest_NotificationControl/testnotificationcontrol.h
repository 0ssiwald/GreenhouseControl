#pragma once

#include <QObject>
#include <QtTest>
#include "notification_control.h"
#include "notification.h"


class TestNotificationControl : public QObject {
    Q_OBJECT

    NotificationControl* sut;
    Notification* notification1_;
    Notification* notification2_;

public:
    explicit TestNotificationControl(QObject *parent = nullptr)  : QObject(parent) {}

private slots:
    void init();
    void initTestCase();
    void cleanupTestCase();
    void cleanup();

    //tests
    void testloadNotificationsFromFile();
    void testDeleteNotification();
    void testAddNotificationToVector();
    void testUpdateActiveNotificationList();
};

