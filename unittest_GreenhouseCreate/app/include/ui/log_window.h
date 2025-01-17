#ifndef LOG_WINDOW_H
#define LOG_WINDOW_H

// For logWindow
#include "log.h"
#include <QWidget>
#include <QObject>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QListWidgetItem>
#include <QMessageBox>
#include <QString>

class LogWindow: public QWidget {
    Q_OBJECT
public:
    explicit LogWindow(SystemLog* systemLog, QWidget* parent = nullptr);
    ~LogWindow();

private:
    QListWidget* fileListWidget;
    SystemLog* systemLog_;
    QTextEdit* logTextEdit;
    void populateFileList();

private slots:
    void onFileSelected(QListWidgetItem* item);
};


#endif // LOG_WINDOW_H
