#include <QtTest>
#include "greenhouse/condition.h"


class TestCondition : public QObject {
    Q_OBJECT

    Condition* sut;

public:
    explicit TestCondition(QObject *parent = nullptr)  : QObject(parent) {}

private slots:
    void init();
    void cleanup();

    //tests
    void testGetFertilazersAsString();
    void testAddFertilizer();
};

