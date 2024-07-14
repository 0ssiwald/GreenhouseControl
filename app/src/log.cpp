#include "log.h"

// Define and initialize static data members
QString SystemLog::log_folder_name_ = "logs";
QString SystemLog::log_file_name_;


void SystemLog::initLogging() {
    // create folder for logfiles if not exists
    if(!QDir(log_folder_name_).exists()) {
        QDir().mkdir(log_folder_name_);
    }

    // Create Log File Name form the date
    log_file_name_ = QString("%1/log_%2.txt").arg(log_folder_name_, QDateTime::currentDateTime().toString("yyyy_MM_dd"));
    //Install the costom message handler to write the logs to a file instead of stderr
    qInstallMessageHandler(myMessageHandler);
}

// Custom massage handler
void SystemLog::myMessageHandler(QtMsgType type, const QMessageLogContext &context, const QString &message) {
    (void)context; // Suppress unused parameter warning

    QFile logFile(log_file_name_);
    if (!logFile.open(QIODevice::Append | QIODevice::Text))
        return;

    QTextStream out(&logFile);
    QString logType;

    switch (type) {
    case QtDebugMsg:
        logType = "DEBUG";
        break;
    case QtInfoMsg:
        logType = "INFO";
        break;
    case QtWarningMsg:
        logType = "WARNING";
        break;
    case QtCriticalMsg:
        logType = "CRITICAL";
        break;
    case QtFatalMsg:
        logType = "FATAL";
        break;
    }

    // Get the current date and time as a string
    QString dateTimeString = QDateTime::currentDateTime().toString("dd.MM.yyyy HH:mm:ss");

    out << dateTimeString << " [" << logType << "] : " << message << Qt::endl;
    logFile.close();
}

