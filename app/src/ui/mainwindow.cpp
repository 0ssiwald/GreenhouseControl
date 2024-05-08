#include "ui/mainwindow.h"
#include "ui/log_window.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(std::shared_ptr<Greenhouse> gh, std::shared_ptr<SystemLog> log, QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), greenhouse(gh), system_log_(log) {
    ui->setupUi(this);

    // Populate the QGridLayout
    for(int group_row = 0; group_row <= greenhouse->getNumberOfRows(); ++group_row) {
        for(int group_col = 0; group_col <= greenhouse->getNumberOfColumns(); ++group_col) {
            // First an empty group is created and if a real group is found it gets overwritten
             QGroupBox* groupBox = new QGroupBox("Empty group", this);
            for(auto &it: greenhouse->getPlantGroups()) {
                if(it->getGridRowNumber() == group_row && it->getGridColumnNumber() == group_col) {

                    groupBox->setTitle(QString("Group (%1, %2)").arg(group_row).arg(group_col));
                    // Create a container QWidget to hold the QGridLayout
                    QWidget *container = new QWidget();
                    // Create a QGridLayout
                    QGridLayout *gridLayoutPlants = new QGridLayout(container);
                    // Set the grid layout as the layout for the container widget
                    container->setLayout(gridLayoutPlants);
                     // Set the container as the layout of the group box
                    groupBox->setLayout(new QVBoxLayout);
                    groupBox->layout()->addWidget(container);

                    for(int plant_row = 0; plant_row <= it->getNumberOfPlantRows(); ++plant_row) {
                        for(int plant_column = 0; plant_column <= it->getNumberOfPlantColumns(); ++plant_column) {

                            QLabel* plantLabel = new QLabel();
                            for(auto &it2: it->getPlants()) {
                                if(it2->getGridRowNumber() == plant_row && it2->getGridColumnNumber() == plant_column) {
                                    plantLabel->setFrameStyle(QFrame::Box | QFrame::Raised);
                                    plantLabel->setAlignment(Qt::AlignCenter);
                                    plantLabel->setText(QString("Plant (%1, %2)").arg(plant_row).arg(plant_column));
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


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateTemperatureLabel(float temperature) {
    ui->temperatureLabel->setText(QString("Temperatur: %1 °C").arg(QString::number(temperature, 'f', 1)));
}

void MainWindow::updateHumidityLabel(float humidity) {
    ui->humidityLabel->setText(QString("Luftfeuchtigkeit: %1%").arg(QString::number(humidity, 'f', 1))); // 'f', 1 -> eine Nachkommastelle
}

void MainWindow::on_systemLogButton_clicked()
{
    // Create and show a new LogWindow (nullptr -> no parent to open as a new window)
    LogWindow* logWindow = new LogWindow(system_log_, nullptr);
    logWindow->show();
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







