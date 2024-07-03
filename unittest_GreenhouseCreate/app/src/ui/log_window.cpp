#include "ui/log_window.h"

LogWindow::~LogWindow() {
    delete fileListWidget;
    delete logTextEdit;
}

LogWindow::LogWindow(SystemLog* systemLog, QWidget* parent)
    : QWidget(parent), systemLog_(std::move(systemLog)) {
    setWindowTitle("System Log");

    // Create layout
    QVBoxLayout* layout = new QVBoxLayout(this);

    // Create file list widget
    fileListWidget = new QListWidget(this);
    layout->addWidget(fileListWidget);

    // Create text edit widget
    logTextEdit = new QTextEdit(this);
    layout->addWidget(logTextEdit);

    // Stretch factors control the proportion of the layout occupied by each widget
    // In this case, QTextEdit will take up twice the space as QListWidget
    layout->setStretch(0, 1); // QListWidget
    layout->setStretch(1, 2); // QTextEdit

    // Populate the list of files
    populateFileList();

    // Connect the item clicked signal to a slot function
    connect(fileListWidget, &QListWidget::itemClicked, this, &LogWindow::onFileSelected);
    // Set the initial size of the window
    resize(600, 800);

}

void LogWindow::populateFileList() {
    QDir dir;
    dir.setPath(systemLog_->getFolderName());
    QStringList filters;
    filters << "*.txt"; // Add a filter for text files

    // Get the list of files that match the filter
    QStringList fileList = dir.entryList(filters, QDir::Files);

    // Add the files to the file list widget
    for (const QString &fileName : fileList) {
        fileListWidget->addItem(fileName);
    }
}

void LogWindow::onFileSelected(QListWidgetItem* item) {
    QString fileName = item->text();
    QString filePath = systemLog_->getFolderName()+ "/" + fileName;
    // Open and read the selected file
    QFile file(filePath);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        // Display the content in the text edit
        logTextEdit->setPlainText(in.readAll());
        file.close();
    } else {
        QMessageBox::warning(this, "Fehler", "Datei konnte nicht geöffnet werden: " + fileName);
    }
}
