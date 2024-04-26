#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(std::shared_ptr<Greenhouse> gh, QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), greenhouse(gh)
{
    ui->setupUi(this);

    // Populate the QGridLayout with PlantGroupWidget instances
    for (int row = 0; row < greenhouse->number_of_group_rows; ++row) {
        for (int col = 0; col < greenhouse->number_of_group_columns; ++col) {
            QLabel* groupLabel = new QLabel(this);
            groupLabel->setFrameStyle(QFrame::Box | QFrame::Raised);
            groupLabel->setAlignment(Qt::AlignCenter);
            groupLabel->setText(QString("Group (%1, %2)").arg(row).arg(col));
            ui->gridLayout->addWidget(groupLabel, row, col);
        }
    }
}

MainWindow::~MainWindow()
{
    delete ui;
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



