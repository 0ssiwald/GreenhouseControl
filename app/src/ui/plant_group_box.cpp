#include "ui/plant_group_box.h"
#include "ui/group_dialog.h"

PlantGroupBox::PlantGroupBox(QWidget* parent)
    : QGroupBox(parent) {
    // So that the box is invisible at first
    setStyleSheet("QGroupBox { border: none; }");

}

QGridLayout* PlantGroupBox::setPlantGroupLayout(int group_number) {
    // To be able to click on the box
    setMouseTracking(true);
    // Connect the group box clicked signal to the openNewWindow slot
    connect(this, &PlantGroupBox::box_clicked, this, &PlantGroupBox::on_Box_clicked);
    // Shows a Frame around the Box and a tilte
    setStyleSheet("QGroupBox { border: -; }");
    setTitle(QString("Gruppe %1").arg(group_number));
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
    GroupDialog* groupDialog = new GroupDialog(plant_group_, group_number_);
    groupDialog->show();
}
