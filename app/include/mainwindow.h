#pragma once

#include <QMainWindow>
#include <QLabel>
#include <memory>
#include "ui_mainwindow.h" // because Ui::MainWindow class is an incomplete type at the point where you're trying to access its members.
#include "greenhouse.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(std::shared_ptr<Greenhouse> gh, QWidget *parent = nullptr);
    ~MainWindow();

    void updateTemperatureLabel(float);
    void updateHumidityLabel(float);

private slots:


private:
    Ui::MainWindow *ui;
    std::shared_ptr<Greenhouse> greenhouse;

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

