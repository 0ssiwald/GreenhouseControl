#ifndef PLANT_GROUP_BOX_H
#define PLANT_GROUP_BOX_H

#include <QGroupBox>
#include <QMouseEvent>
#include <QGridLayout>
#include "greenhouse/plant_group.h"



class PlantGroupBox: public QGroupBox {
    Q_OBJECT
private:
    PlantGroup* plant_group_;
public:
    explicit PlantGroupBox(QWidget* parent = nullptr);
    void setPlantGroup(PlantGroup* plant_group) {plant_group_ = plant_group;}
    QGridLayout* setPlantGroupLayout();
protected:
    // Reimplement the mousePressEvent to detect clicks on the group box
    void mousePressEvent(QMouseEvent* event) override;
signals:
    void box_clicked();
private slots:
    void on_Box_clicked();
};

#endif // PLANT_GROUP_BOX_H
