#include <QtTest>
#include "greenhouse/plant_group.h"


class TestPlantGroup : public QObject {
    Q_OBJECT

    PlantGroup* sut;
    Plant* plant1_;
    Plant* plant2_;
    Note* note1_;
    Note* note2_;

public:
    explicit TestPlantGroup(QObject *parent = nullptr)  : QObject(parent) {}

private slots:
    void init();
    void cleanup();
    void initTestCase();
    void cleanupTestCase();

    //tests
    void testSetPlantGridSize();
    void testSetGridPosition();
    void testAddPlantToGrid();
    void testRemoveNote();
};

