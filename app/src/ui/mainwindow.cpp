#include "ui/mainwindow.h"
#include "ui/plant_group_box.h"
#include "ui/log_window.h"
#include <QPalette>

MainWindow::MainWindow(Greenhouse* gh, SystemLog* log, NotificationControl* notification, WaterControl *water, SensorControl *sensor, QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), greenhouse_(gh), systemLog_(log), notificationControl_(notification), waterControl_(water), sensorControl_(sensor) {
    ui->setupUi(this);
    // Make the valve button not visible only the icon
    ui->mainValveToggleButton->setStyleSheet("QPushButton { background-color: transparent; border: 0px }");
    ui->fireAlarmButton->setStyleSheet("QPushButton { background-color: transparent; border: 0px }");
    setGroupLayout();
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::addPlantLabel(PlantLabel* plantLabel, Plant* plant) {
    plantLabel->setPlantLabelLayout();
    plantLabel->setProperty("plant_name", QString::fromStdString(plant->getPlantName()));
    // setting the water valve and the soil sensor so that the plant lable can display them
    plantLabel->setWaterValve(plant->getWaterValve());
    plantLabel->setMoistureSensor(plant->getSoilSensor());

    plantLabels_.push_back(plantLabel);
}

// Create the main Layout of Plant Groups and Plants
void MainWindow::setGroupLayout() {
    // Populate the QGridLayout
    for(unsigned int group_row = 0; group_row <= greenhouse_->getNumberOfRows(); ++group_row) {
        for(unsigned int group_col = 0; group_col <= greenhouse_->getNumberOfColumns(); ++group_col) {
            // First an empty groupBox is created and if a real group is found it gets overwritten
            PlantGroupBox* groupBox = new PlantGroupBox(this);
            for(auto &group: greenhouse_->getPlantGroups()) {
                if(group->getGridRowNumber() == group_row && group->getGridColumnNumber() == group_col) {
                    groupBox->setPlantGroup(group);
                    // Configure the Layout of the group Box
                    QGridLayout *gridLayoutPlants = groupBox->setPlantGroupLayout();
                    for(unsigned int plant_row = 0; plant_row <= group->getNumberOfPlantRows(); ++plant_row) {
                        for(unsigned int plant_column = 0; plant_column <= group->getNumberOfPlantColumns(); ++plant_column) {
                            PlantLabel* plantLabel = new PlantLabel();
                            for(auto &plant: group->getPlants()) {
                                if(plant->getGridRowNumber() == plant_row && plant->getGridColumnNumber() == plant_column) {
                                    // Adding the sensor and valve to the corrisponding label
                                    addPlantLabel(plantLabel, plant);
                                    break;
                                }
                            }
                            gridLayoutPlants->addWidget(plantLabel, plant_row, plant_column);
                        }
                    }

                }
            }
            ui->gridLayout->addWidget(groupBox, group_row, group_col);
        }
    }
}


void MainWindow::updateTemperatureLabel(float temperature) {
    ui->temperatureLabel->setText(QString("Temperatur: %1 °C").arg(QString::number(temperature, 'f', 1)));
}

void MainWindow::updateHumidityLabel(float humidity) {
    ui->humidityLabel->setText(QString("Luftfeuchtigkeit: %1%").arg(QString::number(humidity, 'f', 1))); // 'f', 1 -> eine Nachkommastelle
}

// Plant Labels get updated with the moisture Value and the right colour
void MainWindow::updatePlantLabels() {
    bool main_valve_is_open = waterControl_->isMainValveOpen();
    bool flow_is_detected = waterControl_->getFlowSensor()->isFlowDetected();
    for(auto &it: plantLabels_) {
        it->updatePlantLabel(main_valve_is_open, flow_is_detected);
    }
}

void MainWindow::on_systemLogButton_clicked() {
    // Create and show a new LogWindow (nullptr -> no parent to open as a new window)
    LogWindow* logWindow = new LogWindow(systemLog_, nullptr);
    logWindow->show();
}

// Displays the Notification List
void MainWindow::setNotificationList() {
    ui->notificationListWidget->clear();
    for(size_t notification_number = 0; notification_number < notificationControl_->getActiveNotificationList().size(); notification_number++) {
        QString notification_string = QString::fromStdString(notificationControl_->getActiveNotificationList()[notification_number]->getNotificationMessage());
        // other widgets like ui->notificationWidget set as parents to handle freeing the memory
        QWidget* notificationWidget = new QWidget(ui->notificationListWidget);
        QHBoxLayout* layout = new QHBoxLayout(notificationWidget);
        QLabel* notificationLabel = new QLabel(notification_string, notificationWidget);
        // Set maximum width for the QLabel to handle line breaks
        notificationLabel->setWordWrap(true);
        QCheckBox* deleteCheckBox = new QCheckBox(notificationWidget);
        // Store the note index as a property of the Check Box
        deleteCheckBox->setProperty("notificationIndex", int(notification_number));
        connect(deleteCheckBox, &QCheckBox::clicked, this, &MainWindow::deleteNotification);
        // Set the focus policy of the delete button
        deleteCheckBox->setFocusPolicy(Qt::NoFocus);
        // Set the size policy of the delete button to be fixed
        deleteCheckBox->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        // Adjust the size of the delete button
        deleteCheckBox->setFixedSize(24, 24);
        layout->addWidget(notificationLabel);
        layout->addWidget(deleteCheckBox);
        notificationWidget->setLayout(layout);
        // Create a QListWidgetItem and set the custom widget as its item widget
        QListWidgetItem* item = new QListWidgetItem(ui->notificationListWidget);
        item->setSizeHint(notificationWidget->sizeHint());
        ui->notificationListWidget->addItem(item);
        ui->notificationListWidget->setItemWidget(item, notificationWidget);
    }
}

void MainWindow::deleteNotification() {
    // Get the sender of the signal, which is the delete button clicked
    QCheckBox* deleteCheckBox = qobject_cast<QCheckBox*>(sender());

    if (deleteCheckBox) {
        // Get the index stored as a property of the delete button
        unsigned int notificationIndex = deleteCheckBox->property("notificationIndex").toInt();
        // Ensure the index is valid
        if (notificationIndex < notificationControl_->getActiveNotificationList().size()) {
            notificationControl_->deleteNotification(notificationIndex);
            // Update the list
            setNotificationList();
        }
    }
}

void MainWindow::on_mainValveToggleButton_toggled(bool checked) {
    if(checked){
        waterControl_->openMainValve();
        qInfo().noquote() << "Main valve was opend";
    }
    else{
        waterControl_->closeMainValve();
        qInfo().noquote() << "Main valve was closed";
    }
}

void MainWindow::toggleMainValveToggleButtonOff() {
    if( ui->mainValveToggleButton->isChecked()) {
        // Create a message box
        QMessageBox* warningBox = new QMessageBox(QMessageBox::Warning, "Warnung",
            "Unregelmäßgier Wasserfluss regestriert. Hauptventil wird geschlossen", QMessageBox::Ok, this);
        // Show the message box without blocking the UI
        warningBox->show();
    }
    // Open main valve
    ui->mainValveToggleButton->setChecked(false);
}

void MainWindow::on_waterSlider_sliderMoved(int position) {
    waterControl_->getFlowSensor()->setMeasurent(float(position));
}

void MainWindow::changeWaterSlider() {
    float flow_amount = waterControl_->getFlowSensor()->getMeasurement();
    ui->waterSlider->setValue(int(flow_amount));
}

void MainWindow::fireAlarm() {
    // Create a message box
    QMessageBox* warningBox = new QMessageBox(QMessageBox::Warning, "Feueralarm",
                                              "Rauch detektiert, bitte leiten Sie Löschmaßnamen ein!", QMessageBox::Ok, this);
    this->setStyleSheet("QMainWindow {"
                        "background-image: url(:/pictures/FireIconOnWithoutBorder.png);"
                        "background-position: center;"  // Position the image in the center
                        "background-repeat: no-repeat;"  // Do not repeat the image
                        "background-size: 50% 50%;"      // Set the size of the image (50% of the width and height of the window)
                        "}");
    //warningBox->setStyleSheet("background: #f5350a");
    // Show the message box without blocking the UI
    warningBox->show();
    // Close main valve to fight the fire
    ui->mainValveToggleButton->setChecked(true);
}


void MainWindow::on_fireAlarmButton_toggled(bool checked) {
    if(checked) {
        emit fireAlarmTriggered();
    } else {
        this->setStyleSheet("");  // Reset the stylesheet to remove the background image
    }
}

