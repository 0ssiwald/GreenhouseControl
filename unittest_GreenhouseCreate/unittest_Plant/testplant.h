#include <QtTest>
#include "greenhouse/plant.h"


class TestPlant : public QObject {
    Q_OBJECT

    Plant* sut;
    std::chrono::system_clock::time_point*  mock_sowing_date_;
    PlantProfile* mock_profile_;

public:
    explicit TestPlant(QObject *parent = nullptr)  : QObject(parent) {}

private slots:
    void initTestCase();
    void cleanupTestCase();

    //tests
    void testSetGridPosition();
};

