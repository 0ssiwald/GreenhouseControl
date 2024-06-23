#include "testlog.h"


void TestLog::initTestCase() {
    // Ensure the logs directory is clean before testing
    if (QDir(sut->getFolderName()).exists()) {
        QDir(sut->getFolderName()).removeRecursively();
    }
}

void TestLog::cleanupTestCase() {
    // Clean up the logs directory after testing
    if (QDir(sut->getFolderName()).exists()) {
        QDir(sut->getFolderName()).removeRecursively();
    }
}

void TestLog::init() {
    sut = new SystemLog;
}

void TestLog::cleanup() {
    delete sut;
}

void TestLog::testInitLogging() {
    sut->initLogging();

    // Check if the log folder exists
    QVERIFY(QDir(sut->getFolderName()).exists());

    // Check if the log file is created
    QFile logFile(sut->getFolderName());
    QVERIFY(logFile.exists());
}

void TestLog::testMyMessageHandler() {
    sut->initLogging();

    // Redirect qDebug, qInfo, etc. to our custom message handler
    qInstallMessageHandler(SystemLog::myMessageHandler);

    // Log some messages
    qDebug() << "This is a debug message";
    qInfo() << "This is an info message";
    qWarning() << "This is a warning message";
    qCritical() << "This is a critical message";
    // Note: qFatal will terminate the application, so we cannot test it here

    // Read the log file and verify the contents
    QFile logFile(sut->getFileName());
    QVERIFY(logFile.open(QIODevice::ReadOnly | QIODevice::Text));
    QTextStream in(&logFile);

    QStringList logEntries;
    while (!in.atEnd()) {
        logEntries << in.readLine();
    }
    logFile.close();

    QVERIFY(logEntries.size() >= 4); // Check if at least four messages are logged

    // Verify each log entry
    QVERIFY(logEntries[0].contains("DEBUG"));
    QVERIFY(logEntries[0].contains("This is a debug message"));

    QVERIFY(logEntries[1].contains("INFO"));
    QVERIFY(logEntries[1].contains("This is an info message"));

    QVERIFY(logEntries[2].contains("WARNING"));
    QVERIFY(logEntries[2].contains("This is a warning message"));

    QVERIFY(logEntries[3].contains("CRITICAL"));
    QVERIFY(logEntries[3].contains("This is a critical message"));
}

QTEST_APPLESS_MAIN(TestLog);
