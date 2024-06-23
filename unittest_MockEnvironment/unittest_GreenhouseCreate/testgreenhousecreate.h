#include <QtTest>
#include "greenhouse/greenhouse_create.h"

class TestGreenhouseCreate : public QObject {
    Q_OBJECT

    GreenhouseCreate *sut;

public:
    explicit TestGreenhouseCreate(QObject *parent = nullptr)  : QObject(parent) {}

private slots:
    void init();
    void cleanup();
    void initTestCase();
    void cleanupTestCase();

    //test
    void testLoadGreenhouseFromFile();
};
