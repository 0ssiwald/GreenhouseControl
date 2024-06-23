#pragma once

#include <QObject>
#include <QtTest>
#include "notification.h"


class TestNotification : public QObject {
    Q_OBJECT

    Notification* sut;

public:
    explicit TestNotification(QObject *parent = nullptr)  : QObject(parent) {}

private slots:
    void initTestCase();
    void cleanupTestCase();

    //tests
    void testIsNotificationTheSameForAnotherPlant();
    void testGetNotificationMessage();
};
