#include "ui/plant_group_box.h"
#include "ui/group_dialog.h"

PlantGroupBox::PlantGroupBox(QWidget* parent)
    : QGroupBox(parent) {
    // So that the box is invisible at first
    setStyleSheet("QGroupBox { border: none; }");

}

QGridLayout* PlantGroupBox::setPlantGroupLayout() {
    // To be able to click on the box
    setMouseTracking(true);
    // Connect the group box clicked signal to the openNewWindow slot
    connect(this, &PlantGroupBox::box_clicked, this, &PlantGroupBox::on_Box_clicked);
    // Shows a Frame around the Box and a tilte
    //setStyleSheet("QGroupBox { border: -; }");
    //setStyleSheet("QGroupBox { border-color : #7a361f;}");
    setStyleSheet("QGroupBox {border: 2px solid #7a361f; border-radius: 5px; margin-top: 1ex; }"
                  "QGroupBox::title { subcontrol-origin: margin; subcontrol-position: top center; padding: 0 3px; }");
    setTitle(QString("Gruppe %1").arg(QString::fromStdString(plant_group_->getGroupName())));
    // Create a container QWidget to hold the QGridLayout
    QWidget *container = new QWidget();
    // Create a QGridLayout
    QGridLayout *gridLayoutPlants = new QGridLayout(container);
    // Set the grid layout as the layout for the container widget
    setLayout(gridLayoutPlants);
    layout()->addWidget(container);
    return gridLayoutPlants;
}

void PlantGroupBox::mousePressEvent(QMouseEvent* event)  {
    if (event->button() == Qt::LeftButton) {
        // Open a new window when the group box is clicked
        emit box_clicked();
    }
    QGroupBox::mousePressEvent(event);
}

void PlantGroupBox::on_Box_clicked() {
    GroupDialog* groupDialog = new GroupDialog(plant_group_, QString::fromStdString(plant_group_->getGroupName()));
    groupDialog->show();
}
