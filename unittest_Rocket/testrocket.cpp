#include "testrocket.h"

#include <iostream>

#include <math.h>

using namespace std;

void TestRocket::init()
{
    sut = new logic::RocketImpl(100.0, 100.0);
    spy = new QSignalSpy(sut, SIGNAL(rocketMovementUpdate(float, float, float)));
}

void TestRocket::cleanup()
{
    delete sut;
    sut = nullptr;
    delete spy;
    spy = nullptr;
}

// a relative position of (100.0, 100.0) to origin (100.0, 100.0) position
// should be (200.0, 200.0) with an default angle of 0.0
void TestRocket::testSetRelativePosition()
{
    sut->setRelativePosition(100.0, 100.0);

    QVERIFY(spy->count() == 1);    // one signal emitted

    // Check params of signal
    QList<QVariant> arguments = spy->takeLast();
    QVERIFY(qFuzzyCompare(arguments.at(0).toFloat(), 200.0f));
    QVERIFY(qFuzzyCompare(arguments.at(1).toFloat(), 200.0f));
    QVERIFY(qFuzzyCompare(arguments.at(2).toFloat(), 0.0f));
}

// setting an angle to 1.0 should result in the very angle of 1.0 and
// the default position of (100.0, 100.0)
void TestRocket::testSetRelativeAngle()
{
    sut->setAngle(1.0);

    QVERIFY(spy->count() == 1);    // one signal emitted

    // Check params of signal
    QList<QVariant> arguments = spy->takeLast();
    QVERIFY(qFuzzyCompare(arguments.at(0).toFloat(), 100.0f));
    QVERIFY(qFuzzyCompare(arguments.at(1).toFloat(), 100.0f));
    QVERIFY(qFuzzyCompare(arguments.at(2).toFloat(), 1.0f));
}

QTEST_APPLESS_MAIN(TestRocket);
