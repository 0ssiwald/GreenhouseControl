#include "testgreenhouse.h"

unsigned int group_grid_row_number;
unsigned int group_grid_column_number;
std::vector<Plant*> mock_plants;

unsigned int PlantGroup::getGridRowNumber() {
    return group_grid_row_number;
}
unsigned int PlantGroup:: getGridColumnNumber() {
    return group_grid_column_number;
}
void PlantGroup::setGridPosition(unsigned int row_number,unsigned int column_number) {
    group_grid_row_number = row_number;
    group_grid_column_number = column_number;
}

std::vector<Plant*> PlantGroup::getPlants() {
    return mock_plants;
}


void TestGreenhouse::init() {
    sut = new Greenhouse;
    QVERIFY(sut->getNumberOfRows()== 0);
    QVERIFY(sut->getNumberOfColumns() == 0);
    QVERIFY(sut->getPlantGroups().empty());
}

void TestGreenhouse::cleanup() {
    delete sut;
}

void TestGreenhouse::initTestCase() {
    plant_group1= new PlantGroup;
    plant_group2= new PlantGroup;
}

void TestGreenhouse::cleanupTestCase() {
    delete plant_group1;
    delete plant_group2;
}

void TestGreenhouse::testSetGroupGridSize() {
    QVERIFY(sut->getNumberOfRows() == 0);
    QVERIFY(sut->getNumberOfColumns() == 0);
    sut->setGroupGridSize(1, 2);
    QVERIFY(sut->getNumberOfRows() == 1);
    QVERIFY(sut->getNumberOfColumns() == 2);
}

void TestGreenhouse::testAddPlantGroupToGrid() {
    // plant_group should not be able to get place 1, 1 because grid is only 0, 0
    QVERIFY(sut->addPlantGroupToGrid(plant_group1, 1, 1) == false);
    QVERIFY(sut->getPlantGroups().empty());
    // Add plat_group1
    QVERIFY(sut->addPlantGroupToGrid(plant_group1, 0, 0) == true);
    QVERIFY(sut->getPlantGroups().size() == 1);
    QVERIFY(group_grid_row_number == 0);
    QVERIFY(group_grid_column_number == 0);
    // Test that plant_group2 cant be added to the same spot
    QVERIFY(sut->addPlantGroupToGrid(plant_group2, 0, 0) == false);
    QVERIFY(sut->getPlantGroups().size() == 1);
}

// Is it ok that this test uses multiple methods?????????
void TestGreenhouse::testgetAllPants() {
    QVERIFY(sut->getAllPlants().empty());
    sut->setGroupGridSize(1, 0);
    // should still be empty because no plants are in the plant group
    sut->addPlantGroupToGrid(plant_group1, 0, 0);
    QVERIFY(sut->getAllPlants().empty());
    // after adding a plant there should be plants that get returned
    Plant p1;
    mock_plants.push_back(&p1);
    sut->addPlantGroupToGrid(plant_group1, 0, 0);
    QVERIFY(sut->getAllPlants().size() == 1);
    sut->addPlantGroupToGrid(plant_group2, 1, 0);
    QVERIFY(sut->getAllPlants().size() == 2);
}

QTEST_APPLESS_MAIN(TestGreenhouse)
