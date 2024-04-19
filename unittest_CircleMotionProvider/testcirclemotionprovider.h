#pragma once

#include <QObject>
#include <QtTest>

#include "circlemotionprovider.h"

// In this example we use a mock-up for the Rocket class.
// The Rocket class is a dependency of CircleMotionProvider and needs thus to be mocked
// if we want to isolate CircleMotionProvider as the SUT.
class RocketMock : public logic::Rocket // Using the Rocket interface
{
public:

    float relX = NAN;
    float relY = NAN;
    float ang = NAN;

    RocketMock() = default;
    virtual ~RocketMock() = default;

    virtual void setRelativePosition(float relativeX, float relativeY) override
    {
        relX = relativeX;
        relY = relativeY;
    }

    virtual void setAngle(float angle) override
    {
        ang = angle;
    }
};



// NOTE:
// The purpose of this class is to demonstrate how to set up a Unit Test with Qt.
// The included test cases are quite incomplete and it is expected that there will be more thorough
// testing in the final projects
class TestCircleMotionProvider : public QObject
{
    Q_OBJECT

    logic::CircleMotionProvider * sut;
    RocketMock * mock;

public:
    explicit TestCircleMotionProvider(QObject *parent = nullptr)  : QObject(parent) {}

private slots:

    // Executed by QtTest before and after test suite
    void initTestCase() {}
    void cleanupTestCase() {}

    // Executed by QtTest before and after each test
    void init();
    void cleanup();

    // tests
    void testFrequency();
    void testAmplitude();
};
