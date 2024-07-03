#include "testflowsensor.h"

void TestFlowSensor::initTestCase() {
    sut = new FlowSensor;
}

void TestFlowSensor::cleanupTestCase() {
    delete sut;
}

void TestFlowSensor::testIsFlowDetected() {
    QVERIFY(!sut->isFlowDetected());
    sut->setMeasurent(2.0);
    QVERIFY(!sut->isFlowDetected()); //flow should not be deteced below threshold
    sut->setMeasurent(5.0);
    QVERIFY(sut->isFlowDetected()); //flow should be detected at 5.0
}


QTEST_APPLESS_MAIN(TestFlowSensor)
