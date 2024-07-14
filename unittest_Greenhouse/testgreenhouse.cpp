#include "testgreenhouse.h"

unsigned int group_grid_row_number = -1;
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
    group_grid_row_number = 0; // reset numbers
    group_grid_column_number = 0;
    sut->setGroupGridSize(0, 0); // reset grid size
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

void TestGreenhouse::testAddPlantGroupToGrid_v_v_v() {
    // the Grid size sets the valid value range for second an thrid parameter
    // The plant can only be added inside the grid size
    sut->setGroupGridSize(1, 2);
    QVERIFY(sut->addPlantGroupToGrid(plant_group1, 1, 1) == true); // function should return true
    QVERIFY(sut->getPlantGroups().size() == 1); // the plant should be added
    QVERIFY(group_grid_row_number == 1); // row and grid numbers should be updated to the new values
    QVERIFY(group_grid_column_number == 1);
}
void TestGreenhouse::testAddPlantGroupToGrid_v_v_ilow() {
    sut->setGroupGridSize(1, 2);
    QVERIFY(sut->addPlantGroupToGrid(plant_group1, 1, -3) == false);
    QVERIFY(sut->getPlantGroups().size() == 0); // the plant should be not added
    QVERIFY(group_grid_row_number == 0); // row and grid numbers should not be updated to the new values
    QVERIFY(group_grid_column_number == 0);
}
void TestGreenhouse::testAddPlantGroupToGrid_v_v_ihigh() {
    sut->setGroupGridSize(1, 2);
    QVERIFY(sut->addPlantGroupToGrid(plant_group1, 1, 3) == false);
    QVERIFY(sut->getPlantGroups().size() == 0); // the plant should be not added
    QVERIFY(group_grid_row_number == 0); // row and grid numbers should not be updated to the new values
    QVERIFY(group_grid_column_number == 0);
}
void TestGreenhouse::testAddPlantGroupToGrid_v_ilow_v() {
    sut->setGroupGridSize(1, 2);
    QVERIFY(sut->addPlantGroupToGrid(plant_group1, -3, 2) == false);
    QVERIFY(sut->getPlantGroups().size() == 0); // the plant should be not added
    QVERIFY(group_grid_row_number == 0); // row and grid numbers should not be updated to the new values
    QVERIFY(group_grid_column_number == 0);
}
void TestGreenhouse::testAddPlantGroupToGrid_v_ihigh_v() {
    sut->setGroupGridSize(1, 2);
    QVERIFY(sut->addPlantGroupToGrid(plant_group1, 3, 2) == false);
    QVERIFY(sut->getPlantGroups().size() == 0); // the plant should be not added
    QVERIFY(group_grid_row_number == 0); // row and grid numbers should not be updated to the new values
    QVERIFY(group_grid_column_number == 0);
}
void TestGreenhouse::testAddPlantGroupToGrid_i_v_v() {
    sut->setGroupGridSize(1, 2);
    QVERIFY(sut->addPlantGroupToGrid(nullptr, 1, 2) == false);
    QVERIFY(sut->getPlantGroups().size() == 0); // the plant should be not added
    QVERIFY(group_grid_row_number == 0); // row and grid numbers should not be updated to the new values
    QVERIFY(group_grid_column_number == 0);
}

void TestGreenhouse::testgetAllPants() {
    QVERIFY(sut->getAllPlants().empty());
    sut->setGroupGridSize(1, 0);
    // after adding a plant there should be plants that get returned
    Plant p1;
    mock_plants.push_back(&p1);
    sut->addPlantGroupToGrid(plant_group1, 0, 0);
    QVERIFY(sut->getAllPlants().size() == 1);
    sut->addPlantGroupToGrid(plant_group2, 1, 0);
    QVERIFY(sut->getAllPlants().size() == 2);
}

QTEST_APPLESS_MAIN(TestGreenhouse)
