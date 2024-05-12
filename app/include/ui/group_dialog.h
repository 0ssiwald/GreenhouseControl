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
    // parameter that indecates if the notesListWidget is shown
    bool in_writing_note_context_ = false;
    // parameter that determines if the addNoteButton creates a new note or just eddits the message of a note
    bool is_edit_ = false;
    Ui::GroupDialog *ui;
    std::shared_ptr<PlantGroup> plantGroup_;
    int group_number_;
    int selected_plant_ = 0;
    void setWeekList(int);
    void setNoteList();

private slots:
    void setDisplayGroupValues(QListWidgetItem*);
    void setConditionWeeklyValues(QListWidgetItem*);
    void on_addNoteButton_clicked();
    void deleteNote();
    void on_notesListWidget_itemDoubleClicked(QListWidgetItem*);
};



#endif // GROUP_DIALOG_H
