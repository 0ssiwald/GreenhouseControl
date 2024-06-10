#include "testplant.h"

void TestPlant::initTestCase() {
    mock_sowing_date_ = new std::chrono::system_clock::time_point;
    *mock_sowing_date_ = std::chrono::system_clock::now();
    mock_profile_ = new PlantProfile;
    sut = new Plant("plant_name",  *mock_sowing_date_, mock_profile_);
    QVERIFY(sut->getGridRowNumber()== 0);
    QVERIFY(sut->getGridColumnNumber() == 0);
    QVERIFY(sut->getPlantProfile() == mock_profile_);
    QVERIFY(sut->getPlantName() == "plant_name");
    QVERIFY(sut->getSowingDate() == *mock_sowing_date_);
}

void TestPlant::cleanupTestCase() {
    delete sut;
}

void TestPlant::testSetGridPosition() {
    sut->setGridPosition(1, 2);
    QVERIFY(sut->getGridRowNumber() == 1);
    QVERIFY(sut->getGridColumnNumber() == 2);
}

QTEST_APPLESS_MAIN(TestPlant)
