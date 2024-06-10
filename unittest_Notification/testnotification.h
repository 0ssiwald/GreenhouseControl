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
    void init();
    void initTestCase();
    void cleanupTestCase();
    void cleanup();

    //tests
    void testIsNotificationTheSameForAnotherPlant();
    void testGetNotificationMessage();
};
