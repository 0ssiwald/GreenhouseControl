#include "testfirealarm.h"

void TestFireAlarm::initTestCase() {
    sut = new FireAlarm;
}

void TestFireAlarm::cleanupTestCase() {
    delete sut;
}

void TestFireAlarm::testSmokeDetected() {
    QSignalSpy spy = QSignalSpy(sut, SIGNAL(sendAlarm()));
    sut->sendAlarm();
    QVERIFY(spy.count() == 1);    // one signal emitted
}


QTEST_APPLESS_MAIN(TestFireAlarm)
