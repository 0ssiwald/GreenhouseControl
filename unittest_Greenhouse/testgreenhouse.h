#include <QtTest>
#include "greenhouse/greenhouse.h"
#include "greenhouse/plant_group.h"

class TestGreenhouse : public QObject {
    Q_OBJECT

    Greenhouse *sut;
    PlantGroup *plant_group1;
    PlantGroup *plant_group2;

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
    // Test with the equivalence class method
    // v == valid parameter range, i == invalid paramter range
    // high == over valid range, low == under valid range
    void testAddPlantGroupToGrid_v_v_v();
    void testAddPlantGroupToGrid_v_v_ihigh();
    void testAddPlantGroupToGrid_v_v_ilow();
    void testAddPlantGroupToGrid_v_ilow_v();
    void testAddPlantGroupToGrid_v_ihigh_v();
    void testAddPlantGroupToGrid_i_v_v();

};
