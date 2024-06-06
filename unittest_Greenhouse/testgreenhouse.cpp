#include "testgreenhouse.h"

void TestGreenhouse::init() {
    mock_plant_group1_ = std::make_shared<MockPlantGroup>();
    mock_plant_group2_ = std::make_shared<MockPlantGroup>();
    mock_plant_group3_ = std::make_shared<MockPlantGroup>();
}

// Is it ok to create the sut in the init Testcases to remove all plant groups???
void TestGreenhouse::cleanup() {}

void TestGreenhouse::initTestCase() {
    sut = new Greenhouse();
    QVERIFY(sut->getNumberOfRows()== 0);
    QVERIFY(sut->getNumberOfColumns() == 0);
    QVERIFY(sut->getPlantGroups().empty());
}

void TestGreenhouse::cleanupTestCase() {
    delete sut;
    sut = nullptr;
}

void TestGreenhouse::testSetGroupGridSize() {
    QVERIFY(sut->getNumberOfRows() == 0);
    QVERIFY(sut->getNumberOfColumns() == 0);
    sut->setGroupGridSize(1, 2);
    QVERIFY(sut->getNumberOfRows() == 1);
    QVERIFY(sut->getNumberOfColumns() == 2);
}

void TestGreenhouse::testAddPlantGroupToGrid() {

}

void TestGreenhouse::testgetAllPants() {
    std::vector<std::shared_ptr<Plant>> plant_vector;
    plant_vector = sut->getAllPlants();
    QVERIFY(plant_vector.size() == 0);
    //sut->?????????

}


QTEST_APPLESS_MAIN(TestGreenhouse)




