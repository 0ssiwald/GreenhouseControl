#pragma once

#include <QMainWindow>
#include <QLabel>
#include <memory>
#include "ui_mainwindow.h" // because Ui::MainWindow class is an incomplete type at the point where you're trying to access its members.
#include "greenhouse.h"

// For logWindow
#include "log.h"
#include <QWidget>
#include <QObject>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QString>
#include "date_time.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(std::shared_ptr<Greenhouse> gh, std::shared_ptr<SystemLog> log, QWidget *parent = nullptr);
    ~MainWindow();

    void updateTemperatureLabel(float);
    void updateHumidityLabel(float);

private slots:
    void on_systemLogButton_clicked();

private:
    Ui::MainWindow *ui;
    std::shared_ptr<Greenhouse> greenhouse;
    std::shared_ptr<SystemLog> system_log_;
    QPushButton* systemLogButton;


   // QLabel *rocketLabel; // This one loads the image  via Qt
   // QPixmap *rocketImg; // Storing same image again, as base for rotation

//public slots:
 //   void moveRocket(float x, float y, float angleRad);

//signals:
//    void start();
//    void stop();

//private slots:
 //   void on_startStopButton_clicked();
 //   void on_centralwidget_customContextMenuRequested(const QPoint &pos);
};


class LogWindow : public QWidget {
    Q_OBJECT
public:
    explicit LogWindow(std::shared_ptr<SystemLog> systemLog, QWidget* parent = nullptr)
        : QWidget(parent), systemLog_(systemLog) {
        setWindowTitle("System Log");

        // Create a QTextEdit to display the log messages
        logTextEdit = new QTextEdit(this);
        logTextEdit->setReadOnly(true);

        // Create a layout and add the QTextEdit to the layout
        QVBoxLayout* layout = new QVBoxLayout(this);
        layout->addWidget(logTextEdit);

        // Set the initial size of the window
        resize(600, 400); // Width: 600, Height: 400

        // Load and display log messages
        displayLogMessages();
    }

    // Method to load and display log messages
    void displayLogMessages() {
        // Clear the current text
        logTextEdit->clear();

        // Load log messages from the systemLog
        std::vector<std::shared_ptr<LogMessage>> logMessages = systemLog_->getLogMessages();

        // Iterate through log messages and display them in the logTextEdit
        for (const auto& logMessage : logMessages) {
            // Convert the log message and timestamp to a readable format
            std::string timestamp = DateTimeConverter::timePointToString(logMessage->time_point_);
            std::string message = logMessage->message_text_;

            // Display the log message and timestamp
            logTextEdit->append(QString::fromStdString(timestamp + " - " + message));
        }
    }

private:
    QTextEdit* logTextEdit;
    std::shared_ptr<SystemLog> systemLog_;
};
