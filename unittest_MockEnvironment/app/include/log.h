#ifndef LOG_H
#define LOG_H

#include <QFile>
#include <QTextStream>
#include <QDateTime>
#include <QDebug>
#include <QLoggingCategory>
#include <QCoreApplication>
#include <QDateTime>
#include <QTime>
#include <QDir>
#include <QString>

class SystemLog {
    static QString log_folder_name_;
    static QString log_file_name_;

public:
    void initLogging();
    // custom massage handler to save the messages to a file instead of printing them to stderr
    static void myMessageHandler(QtMsgType, const QMessageLogContext &, const QString &);
    QString getFolderName() {return log_folder_name_;}
    QString getFileName() {return log_file_name_;}
};

#endif // LOG_H
