#ifndef GROUP_DIALOG_H
#define GROUP_DIALOG_H

#include <memory>
#include <QDialog>
#include "greenhouse/plant_group.h"
#include "ui_group_window.h"

QT_BEGIN_NAMESPACE
namespace Ui { class GroupDialog; }
QT_END_NAMESPACE

class GroupDialog: public QDialog {
    Q_OBJECT
public:
    explicit GroupDialog(std::shared_ptr<PlantGroup> plantGroup, int group_number, QWidget* parent = nullptr);
    ~GroupDialog();

private:
    Ui::GroupDialog *ui;
    std::shared_ptr<PlantGroup> plantGroup_;
    int group_number_;
    int selected_plant_ = 0;
    void setWeekList(int);

private slots:
    void setDisplayGroupValues(QListWidgetItem*);
    void setConditionWeeklyValues(QListWidgetItem*);
};



#endif // GROUP_DIALOG_H
