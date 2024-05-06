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

class SystemLog {
    static QString log_folder_name_;
    static QString log_file_name_;

public:
    void initLogging();
    // custom massage handler to save the messages to a file instead of printing them to stderr
    static void myMessageHandler(QtMsgType, const QMessageLogContext &, const QString &);
    QString getFolderName() {return log_folder_name_;};
};





/*
#include <string>
#include <chrono>
#include <vector>
#include <memory>

struct LogMessage {
    std::string message_text_;
    std::chrono::system_clock::time_point time_point_;
    LogMessage(const std::string& message_text, std::chrono::system_clock::time_point time_point)
        : message_text_(message_text), time_point_(time_point) {}
};


class SystemLog {
    std::string log_file_name_;
    std::vector<std::shared_ptr<LogMessage>> log_messages_;
public:
    SystemLog(const std::string& log_file_name)
        : log_file_name_(log_file_name) {}
    void displayLog();
    void loadLogMessagesFromFile();
    std::vector<std::shared_ptr<LogMessage>> getLogMessages() {return log_messages_;};
    void saveMessageToLog(const std::string&, const std::chrono::system_clock::time_point);
};

*/




#endif // LOG_H
