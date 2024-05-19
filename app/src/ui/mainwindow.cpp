#include "ui/mainwindow.h"
#include "ui/plant_group_box.h"
#include "ui/log_window.h"

MainWindow::MainWindow(std::shared_ptr<Greenhouse> gh, std::shared_ptr<SystemLog> log, NotificationControl* notification, QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), greenhouse_(gh), systemLog_(log), notificationControl_(notification) {
    ui->setupUi(this);

    setGroupLayout();
}


MainWindow::~MainWindow() {
    delete ui;
}

// Create the main Layout of Plant Groups and Plants
void MainWindow::setGroupLayout() {
    // Populate the QGridLayout
    int group_number = 1;
    for(int group_row = 0; group_row <= greenhouse_->getNumberOfRows(); ++group_row) {
        for(int group_col = 0; group_col <= greenhouse_->getNumberOfColumns(); ++group_col) {
            // First an empty groupBox is created and if a real group is found it gets overwritten
            PlantGroupBox* groupBox = new PlantGroupBox(this);
            for(auto &it: greenhouse_->getPlantGroups()) {
                if(it->getGridRowNumber() == group_row && it->getGridColumnNumber() == group_col) {
                    groupBox->setPlantGroup(it);
                    groupBox->setGroupNumber(group_number);
                    // Configure the Layout of the group Box
                    QGridLayout *gridLayoutPlants = groupBox->setPlantGroupLayout(group_number++);
                    int plant_number = 1;
                    for(int plant_row = 0; plant_row <= it->getNumberOfPlantRows(); ++plant_row) {
                        for(int plant_column = 0; plant_column <= it->getNumberOfPlantColumns(); ++plant_column) {
                            PlantLabel* plantLabel = new PlantLabel();
                            for(auto &it2: it->getPlants()) {
                                if(it2->getGridRowNumber() == plant_row && it2->getGridColumnNumber() == plant_column) {
                                    // Adding the sensor to the corrisponding label
                                    plantLabel->setMoistureSensor(it2->getSoilMoistureSensor());
                                    plantLabel->setPlantLabelLayout();
                                    plantLabel->setProperty("plant_number", plant_number++);
                                    // Add label to vector for updating moisture reading in UI
                                    plantLabels_.push_back(plantLabel);
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

void MainWindow::updatePlantLabels() {
    for(auto &it: plantLabels_) {
        // Test if the Moisture Sensor is a nullptr
        if(it->getMoistureSensor()) {
            float soil_moisture = it->getMoistureSensor()->getMeasurementValue();
            QString plant_string = QString("Pflanze %1:\n%2%").arg(QString::number(it->property("plant_number").toInt()), QString::number(soil_moisture, 'f', 1));
            it->setText(plant_string);
        }
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
    for(size_t notification_number = 0; notification_number < notificationControl_->getNotificationList().size(); notification_number++) {
        QString notification_string = notificationControl_->getNotificationList()[notification_number]->getNotificationMessage();
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
        if (notificationIndex < notificationControl_->getNotificationList().size()) {
            notificationControl_->deleteNotification(notificationIndex);
            // Update the list
            setNotificationList();
        }
    }
}


/*

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->rocketLabel = findChild<QLabel *>("rocketLabel");

    // Note the special syntax for resource paths (this loads from a generated qrc file)
    this->rocketImg = new QPixmap(":/rocket.png");  // Need a second copy for rotation in moveRocket(...)

    qDebug() << "Initial window size is" << this->width() << "x" << this->height();
    qDebug() << "Rocket label size is" << this->rocketLabel->size().width() << "x" << this->rocketLabel->size().height();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete rocketImg;
}

void MainWindow::moveRocket(float offsetX, float offsetY, float angleRad)
{
    // Calculate new position taking center window and center rocket image into account
    const float centerImgX = this->rocketLabel->size().width()/2;
    const float centerImgY = this->rocketLabel->size().height()/2;
    const float x = offsetX - centerImgX;
    const float y = offsetY - centerImgY;

    // Reposition label
    this->rocketLabel->move(x, y);

    // Rotate rocket image
    // NOTE: A simple, non-efficient and rather ugly way of rotating a picture.
    // If you don't need this, don't use the following code. Some students required this functionality in the previous semesters.
    QTransform transform;
    transform.rotateRadians(-angleRad + M_PI / 2);
    ui->rocketLabel->setPixmap(this->rocketImg->transformed(transform));
}

void MainWindow::on_startStopButton_clicked()
{
    if (ui->startStopButton->isChecked()) {
        ui->startStopButton->setText("Stop");
        emit start();
    } else {
        ui->startStopButton->setText("Start");
        emit stop();
    }
}

*/







