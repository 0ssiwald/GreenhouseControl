#include "ui/log_window.h"
#include "date_time.h"

    LogWindow::LogWindow(std::shared_ptr<SystemLog> systemLog, QWidget* parent = nullptr)
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

void LogWindow::displayLogMessages() {
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
