#include "testplantgroup.h"

unsigned int plant_grid_row_number;
unsigned int  plant_grid_column_number;

void Plant::setGridPosition(unsigned int row_number,unsigned int column_number) {
    plant_grid_row_number = row_number;
    plant_grid_column_number = column_number;
}
unsigned int Plant::getGridRowNumber() {return plant_grid_row_number;}
unsigned int Plant::getGridColumnNumber() {return plant_grid_column_number;}

void TestPlantGroup::init() {
    sut = new PlantGroup("sut");
    QVERIFY(sut->getNumberOfPlantRows()== 0);
    QVERIFY(sut->getNumberOfPlantColumns() == 0);
    QVERIFY(sut->getPlants().empty());
}

void TestPlantGroup::cleanup() {
    delete sut;
}

void TestPlantGroup::initTestCase() {
    plant1_ = new Plant;
    plant2_ = new Plant;
    note1_ = new Note;
    note2_ = new Note;
}

void TestPlantGroup::cleanupTestCase() {
    delete plant1_;
    delete plant2_;
    delete note1_;
    delete note2_;
}

void TestPlantGroup::testSetPlantGridSize() {
    QVERIFY(sut->getNumberOfPlantRows() == 0);
    QVERIFY(sut->getNumberOfPlantColumns() == 0);
    sut->setPlantGridSize(1, 2);
    QVERIFY(sut->getNumberOfPlantRows() == 1);
    QVERIFY(sut->getNumberOfPlantColumns() == 2);
}
void TestPlantGroup::testSetGridPosition() {
    sut->setGridPosition(1, 2);
    QVERIFY(sut->getGridRowNumber() == 1);
    QVERIFY(sut->getGridColumnNumber() == 2);
}
void TestPlantGroup::testAddPlantToGrid() {
    // plant should not be able to get place 1, 1 because grid is only 0, 0
    QVERIFY(sut->addPlantToGrid(plant1_, 1, 1) == false);
    QVERIFY(sut->getPlants().empty());
    // Add plant1
    QVERIFY(sut->addPlantToGrid(plant1_, 0, 0) == true);
    QVERIFY(sut->getPlants().size() == 1);
    QVERIFY(plant_grid_row_number == 0);
    QVERIFY(plant_grid_column_number == 0);
    // Test that plant_2 cant be added to the same spot
    QVERIFY(sut->addPlantToGrid(plant2_, 0, 0) == false);
    QVERIFY(sut->getPlants().size() == 1);
}

void TestPlantGroup::testRemoveNote() {
    QVERIFY(sut->getNotes().empty());
    // nothing can be removed from empty vector
    QVERIFY(sut->removeNote(0) == false);
    sut->addNote(note1_);
    sut->addNote(note2_);
    QVERIFY(sut->removeNote(2) == false);
    QVERIFY(sut->removeNote(0) == true);
    QVERIFY(sut->removeNote(0) == true);
}

QTEST_APPLESS_MAIN(TestPlantGroup)
