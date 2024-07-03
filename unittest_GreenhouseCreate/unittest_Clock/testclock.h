#pragma once

#include <QObject>
#include <QtTest>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QDir>
#include "clock.h"

using namespace physics;

class TestClock : public QObject {
    Q_OBJECT

    Clock* sut;
    QSignalSpy* updateSpy;

public:
    explicit TestClock(QObject *parent = nullptr)  : QObject(parent) {}

private slots:
    void initTestCase();
    void cleanupTestCase();

    //tests
    void testGetSecondsPerTick();
    void testSetSecondsPerTick();
    void testStart();
    void testStop();
    void testTick();
};
