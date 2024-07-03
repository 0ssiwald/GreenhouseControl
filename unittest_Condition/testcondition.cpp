#include "testcondition.h"


void TestCondition::init() {
    sut = new Condition(5.0, 3.0, 20);
}

void TestCondition::cleanup() {
    delete sut;
}

void TestCondition::testGetFertilazersAsString() {
    Fertilizer fertilizer1 = Fertilizer("test_name1", "test_type1");
    Fertilizer fertilizer2 = Fertilizer("test_name2", "test_type2");
    sut->addFertilizer(&fertilizer1, 10);
    sut->addFertilizer(&fertilizer2, 20);

    QVERIFY(sut->getFertilazersAsString() == "test_name1 10 ml (test_type1)\ntest_name2 20 ml (test_type2)");
}

void TestCondition::testAddFertilizer() {
    Fertilizer fertilizer1 = Fertilizer("test_name", "test_type");

    QVERIFY(sut->getFertilizers().size() == 0);
    sut->addFertilizer(&fertilizer1, 10);
    QVERIFY(sut->getFertilizers().size() == 1);
    QVERIFY(sut->getFertilizers()[0].getAmount() == 10);
}

QTEST_APPLESS_MAIN(TestCondition)
