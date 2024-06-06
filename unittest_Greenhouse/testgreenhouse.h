#include <QtTest>
#include "greenhouse/greenhouse.h"
#include "greenhouse/plant_group.h"

class MockPlant: public Plant {
public:
    MockPlant() = default;
    virtual ~MockPlant() = default;
};

class MockPlantGroup: public PlantGroup {
public:
    int mock_row_number_;
    int mock_column_number_;
    std::vector<MockPlant> mock_plants_;

    MockPlantGroup() = default;
    virtual ~MockPlantGroup() = default;

    virtual int getGridRowNumber() {return mock_row_number_;}
    virtual int getGridColumnNumber() {return mock_column_number_;}
    virtual std::vector<MockPlant> getPlants() {return mock_plants_;}
};




class TestGreenhouse : public QObject {
    Q_OBJECT

    Greenhouse *sut;

    std::shared_ptr<MockPlantGroup> mock_plant_group1_;
    std::shared_ptr<MockPlantGroup> mock_plant_group2_;
    std::shared_ptr<MockPlantGroup> mock_plant_group3_;
    std::vector<std::shared_ptr<PlantGroup>> mock_plant_groups_;

public:
    explicit TestGreenhouse(QObject *parent = nullptr)  : QObject(parent) {}

private slots:
    void init();
    void cleanup();
    void initTestCase();
    void cleanupTestCase();

    //tests
    void testSetGroupGridSize();
    void testgetAllPants();
    void testAddPlantGroupToGrid();
};
