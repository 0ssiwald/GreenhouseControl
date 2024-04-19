#pragma once

#include <QMainWindow>
#include <QLabel>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    QLabel *rocketLabel; // This one loads the image  via Qt
    QPixmap *rocketImg; // Storing same image again, as base for rotation

public slots:
    void moveRocket(float x, float y, float angleRad);

signals:
    void start();
    void stop();

private slots:
    void on_startStopButton_clicked();
};

