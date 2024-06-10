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
    void testAddPlantGroupToGrid();
};
