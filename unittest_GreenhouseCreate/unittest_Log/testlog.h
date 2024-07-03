#pragma once

#include <QObject>
#include <QtTest>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QDir>
#include "log.h"


class TestLog : public QObject {
    Q_OBJECT

    SystemLog* sut;

public:
    explicit TestLog(QObject *parent = nullptr)  : QObject(parent) {}

private slots:
    void init();
    void cleanup();
    void initTestCase();
    void cleanupTestCase();

    //tests
    void testInitLogging();
    void testMyMessageHandler();
};
