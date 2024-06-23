#include <QObject>
#include <QtTest/QtTest>
#include <QSignalSpy>
#include "testclock.h"

void TestClock::initTestCase() {
    sut = new Clock(1);
    updateSpy = new QSignalSpy(sut, &Clock::update);
}

void TestClock::cleanupTestCase() {
    delete updateSpy;
    delete sut;
}

void TestClock::testGetSecondsPerTick() {
    QCOMPARE(sut->getSecondsPerTick(), 1); // Default value should be 5
    sut->setSecondsPerTick(10);
    QCOMPARE(sut->getSecondsPerTick(), 10);
}

void TestClock::testSetSecondsPerTick() {
    sut->setSecondsPerTick(8);
    QCOMPARE(sut->getSecondsPerTick(), 8);
    sut->setSecondsPerTick(3);
    QCOMPARE(sut->getSecondsPerTick(), 3);
}

void TestClock::testStart() {
    sut->start();
    QVERIFY(sut->timer_.isActive());
    QCOMPARE(updateSpy->count(), 1); // Ensure update signal is emitted immediately on start
    sut->stop();
}

void TestClock::testStop() {
    sut->start();
    sut->stop();
    QVERIFY(!sut->timer_.isActive());
}

void TestClock::testTick() {
    sut->start();
    QTest::qWait(1500); // Wait more than one tick interval
    sut->stop();
    QVERIFY(updateSpy->count() >= 2); // Should have at least one tick signal after the initial start
}

QTEST_MAIN(TestClock)

