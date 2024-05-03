#ifndef LOG_WINDOW_H
#define LOG_WINDOW_H

// For logWindow
#include "log.h"
#include <QWidget>
#include <QObject>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QString>


class LogWindow : public QWidget {
    Q_OBJECT
public:
    explicit LogWindow(std::shared_ptr<SystemLog>, QWidget*);

    // Method to load and display log messages
    void displayLogMessages();

private:
    QTextEdit* logTextEdit;
    std::shared_ptr<SystemLog> systemLog_;
};
#endif // LOG_WINDOW_H
