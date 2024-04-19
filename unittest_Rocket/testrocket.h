#pragma once

#include <QObject>
#include <QtTest>

#include "rocket.h"


// NOTE:
// The purpose of this class is to demonstrate how to set up a simple Unit Test with Qt.
// The included test cases are quite incomplete.
class TestRocket : public QObject
{
    Q_OBJECT

    logic::RocketImpl * sut;
    QSignalSpy * spy;

public:
    explicit TestRocket(QObject *parent = nullptr)  : QObject(parent) {}

private slots:

    // Executed by QtTest before and after test case (meaning: all tests in this class)
    void initTestCase() {}
    void cleanupTestCase() {}

    // Executed by QtTest before and after each test function (meaning: every test in this class)
    void init();
    void cleanup();

    // tests
    void testSetRelativePosition();
    void testSetRelativeAngle();
};
