#include "testcirclemotionprovider.h"

#include <iostream>

#include <cmath>

using namespace std;

const float epsilon = 1.0e-4;   // fixed epsilon for comparison of float numbers

void TestCircleMotionProvider::init()
{
    sut = new logic::CircleMotionProvider();
    QVERIFY(sut->getFrequency() == 1.0);
    QVERIFY(sut->getAmplitude() == 100.0);
    QVERIFY(sut->getOffset() == 0.0);
    QVERIFY(sut->directionIsClockwise());

    // Inject dependency to mock-up
    mock = new RocketMock();
    sut->setRocket(mock);
}

void TestCircleMotionProvider::cleanup()
{
    delete sut;
    sut = nullptr;
    delete mock;
    mock = nullptr;

}

// 100.0 ms revolution needs to be complete after 10*10.0 ms steps
void TestCircleMotionProvider::testFrequency()
{
    // Exercise the SUT
    sut->setFrequency(10.0);
    for (int i=0; i < 10; ++i) {
        sut->update(10.0);
    }

    // Check end results
    QVERIFY(abs(mock->relX - 0.0) <= epsilon);
    QVERIFY(abs(mock->relY - 100.0) <= epsilon);
    QVERIFY(abs(mock->ang - -2 * M_PI) <= epsilon);
}

// Amplitude needs to stay constant during a complete revolution
void TestCircleMotionProvider::testAmplitude()
{
    sut->setAmplitude(200);
    sut->setFrequency(10);
    for (int i=0; i < 10; ++i) {
        sut->update(10);

        // Calculate amplitude as length of vector (relX, relY)
        float len = sqrtf(mock->relX * mock->relX + mock->relY * mock->relY);

        // Check that length stays constant at around 200
        QVERIFY(abs(len - 200) <= epsilon);
    }

    // Did one revolution?
    QVERIFY(abs(mock->ang - -2 * M_PI) <= epsilon);
}

QTEST_APPLESS_MAIN(TestCircleMotionProvider);
