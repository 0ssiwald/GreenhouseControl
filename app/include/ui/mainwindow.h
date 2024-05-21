#pragma once

#include <QMainWindow>
#include <QLabel>
#include <QGroupBox>
#include <QCheckBox>
#include <memory>
#include <QtDebug>
#include "ui_mainwindow.h" // because Ui::MainWindow class is an incomplete type at the point where you're trying to access its members.
#include "greenhouse/greenhouse.h"
#include "log.h"
#include "plant_label.h"
#include "control/water_control.h"
#include "notification_control.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(std::shared_ptr<Greenhouse>, std::shared_ptr<SystemLog>, NotificationControl*, WaterControl*, QWidget * = nullptr);
    ~MainWindow();
    void setNotificationList();

private slots:
    void on_systemLogButton_clicked();
    void deleteNotification();
    void on_mainValveToggleButton_toggled(bool);
public slots:
    void updatePlantLabels();
    void updateTemperatureLabel(float);
    void updateHumidityLabel(float);
    void toggleMainValveToggleButtonOff();
private:
    Ui::MainWindow *ui;
    std::shared_ptr<Greenhouse> greenhouse_;
    std::shared_ptr<SystemLog> systemLog_;
    NotificationControl* notificationControl_;
    WaterControl* waterControl_;
    QPushButton* systemLogButton_;
    std::vector<PlantLabel*> plantLabels_;
    void setGroupLayout();
};



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




