#include "ui/group_dialog.h"
#include <QDateTime>
//#include "greenhouse/plant_profile.h"

GroupDialog::GroupDialog(std::shared_ptr<PlantGroup> plantGroup, int group_number, QWidget* parent)
    : QDialog(parent), ui(new Ui::GroupDialog), plantGroup_(plantGroup), group_number_(group_number) {
    ui->setupUi(this);

    // Fill the plantListWidget with the Plants of the Group
    for(unsigned long number_of_plants = 0; number_of_plants < plantGroup->getPlants().size(); number_of_plants++) {
        ui->plantListWidget->addItem(QString("Pflanze: %1").arg(number_of_plants + 1));
    }
    // Ensure the QListWidget is not empty
    if(ui->plantListWidget->count() > 0) {
        // Set the current row to 0 (select the first item)
        ui->plantListWidget->setCurrentRow(0);
        // Retrieve the first item
        QListWidgetItem* firstItem = ui->plantListWidget->item(0);
        // Calling setDisplayGroupValues with the first item in the list
        setDisplayGroupValues(firstItem);
    }
    // Build the Notes of the Group
    setNoteList();

    // Connect the item clicked signal to a slot function
    connect(ui->plantListWidget, &QListWidget::itemClicked, this, &GroupDialog::setDisplayGroupValues);
    connect(ui->weekListWidget, &QListWidget::itemClicked, this, &GroupDialog::setConditionWeeklyValues);
}

// Displays the Values of the selected Plant in the UI
void GroupDialog::setDisplayGroupValues(QListWidgetItem* item) {
    // Check if item is a nullptr before changeing plant_number
    if(item)
        selected_plant_ = ui->plantListWidget->row(item);
    // Ensure the QListWidget is not empty
    if(ui->plantListWidget->count() > 0) {
        ui->groupLabel->setText(QString("Gruppe: %1").arg(group_number_));
        ui->strainLabel->setText(plantGroup_->getPlants()[selected_plant_]->getPlantProfile()->getStrainName());
        ui->soilLabel->setText(plantGroup_->getPlants()[selected_plant_]->getPlantProfile()->getSoilType());
        ui->ageLabel->setText(plantGroup_->getPlants()[selected_plant_]->getSowingDate().toString("dd.MM.yyyy"));
        QString cbd_string = QString("%1%").arg(QString::number(plantGroup_->getPlants()[selected_plant_]->getPlantProfile()->getExpectedCbdContent()));
        ui->cbdLabel->setText(cbd_string);
        QString thc_string = QString("%1%").arg(QString::number(plantGroup_->getPlants()[selected_plant_]->getPlantProfile()->getExpectedThcContent()));
        ui->thcLabel->setText(thc_string);
        QString vegetation_string = QString("%1 Wochen").arg(QString::number(plantGroup_->getPlants()[selected_plant_]->getPlantProfile()->getLengthVegitationPeriod()));
        ui->growLabel->setText(vegetation_string);
        QString flowering_string = QString("%1 Wochen").arg(QString::number(plantGroup_->getPlants()[selected_plant_]->getPlantProfile()->getLengthFloweringPeriod()));
        ui->floweringLabel->setText(flowering_string);

        // Builds the weekly List
        setWeekList(selected_plant_);

    }
}
// Displays the weekly Conditions Values in the UI
void GroupDialog::setConditionWeeklyValues(QListWidgetItem* item) {
    int week_number = 0;
    if(item)
        week_number = ui->weekListWidget->row(item);
    if(ui->weekListWidget->count() > 0) {
        std::shared_ptr<Condition> conditions_weekly = plantGroup_->getPlants()[selected_plant_]->getPlantProfile()->getConditionsWeekly()[week_number];
        QString humidity = QString("%1%").arg(QString::number(conditions_weekly->getHumidity()));
        ui->humidityLabel->setText(humidity);
        QString temperature = QString("%1%").arg(QString::number(conditions_weekly->getTemperature()));
        ui->temperatureLabel->setText(temperature);
        QString lamp_distance = QString("%1 cm").arg(QString::number(conditions_weekly->getLampDistance()));
        ui->lampLabel->setText(lamp_distance);
        QString fertilizer_string_combined;
        for(auto &it: conditions_weekly->getFertilizers()) {
            QString fertilizer_name = QString(it.getFertilizer()->getName());
            QString fertilizer_amount = QString("%1 ml").arg(QString::number(it.getAmount()));
            QString fertilizer_type = QString("(%1)").arg(it.getFertilizer()->getType());
            QString fertilizer_string = QString("%1 %2 %3 \n").arg(fertilizer_name, fertilizer_amount, fertilizer_type);
            fertilizer_string_combined += fertilizer_string;
        }
        ui->fertilizerLabel->setText(fertilizer_string_combined);
    }
}

// selects a Week from the Weekly Conditions
void GroupDialog::setWeekList(int plant_number = 0) {
    ui->weekListWidget->clear();
    unsigned long week_number = 0;
    for(;week_number < plantGroup_->getPlants()[plant_number]->getPlantProfile()->getConditionsWeekly().size(); week_number++) {
        ui->weekListWidget->addItem(QString("Woche: %1").arg( week_number+1));
    }

    // Ensure the QListWidget is not empty
    if(ui->weekListWidget->count() > 0) {
        // Set the current row to 0 (select the first item)
        ui->weekListWidget->setCurrentRow(0);
        // Retrieve the first item
        QListWidgetItem* firstWeeklyItem = ui->weekListWidget->item(0);
        setConditionWeeklyValues(firstWeeklyItem);
    }
}

// Displays the Note List
void GroupDialog::setNoteList() {
    ui->notesListWidget->clear();
    unsigned long note_number = 0;
    for(;note_number < plantGroup_->getNotes().size(); note_number++) {
        QString date_string = QString("%1:\n").arg(plantGroup_->getNotes()[note_number]->getDate().toString("dd.MM.yyyy HH:mm:ss"));
        QString message_string = plantGroup_->getNotes()[note_number]->getMessage();
        QString note_string = date_string + message_string;
        // Create a custom widget to hold the note content and the delete button
        QWidget* noteWidget = new QWidget();
        QHBoxLayout* layout = new QHBoxLayout();
        QLabel* noteLabel = new QLabel(note_string);
        QPushButton* deleteButton = new QPushButton("X");
        deleteButton->setProperty("noteIndex", int(note_number)); // Store the note index as a property of the button
        connect(deleteButton, &QPushButton::clicked, this, &GroupDialog::deleteNote);
        // Set the focus policy of the delete button
        deleteButton->setFocusPolicy(Qt::NoFocus);
        // Set the size policy of the delete button to be fixed
        deleteButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        // Adjust the size of the delete button
        deleteButton->setFixedSize(24, 24);
        layout->addWidget(noteLabel);
        // Add a stretchable space to push the delete button to the right
        layout->addStretch();
        layout->addWidget(deleteButton);
        noteWidget->setLayout(layout);
        // Create a QListWidgetItem and set the custom widget as its item widget
        QListWidgetItem* item = new QListWidgetItem();
        item->setSizeHint(noteWidget->sizeHint());
        ui->notesListWidget->addItem(item);
        ui->notesListWidget->setItemWidget(item, noteWidget);
    }
}


GroupDialog::~GroupDialog() {
    delete ui;
}

void GroupDialog::deleteNote() {
    // Get the sender of the signal, which is the delete button clicked
    QPushButton* deleteButton = qobject_cast<QPushButton*>(sender());

    if (deleteButton) {
        // Get the note index stored as a property of the delete button
        unsigned int noteIndex = deleteButton->property("noteIndex").toInt();
        // Ensure the note index is valid
        if (noteIndex < plantGroup_->getNotes().size()) {
            // Remove the note from the vector
            plantGroup_->removeNote(noteIndex);
            // Update the note list
            setNoteList();
        }
    }
}

void GroupDialog::on_addNoteButton_clicked() {
    in_writing_note_context_ = !in_writing_note_context_;

    if(in_writing_note_context_) {
        ui->notesListWidget->hide();
        ui->noteEdit->clear();
        ui->noteEdit->show();
        ui->addNoteButton->setText("Notiz speichern");
    } else {
        QString text = ui->noteEdit->toPlainText();
        // save only the text to a new note if it is not empty
        if(!text.isEmpty()) {
            // If it is a edited message the note text should only be altered
            if(is_edit_) {
                QListWidgetItem *item = ui->notesListWidget->currentItem();
                int index = ui->notesListWidget->row(item);
                plantGroup_->getNotes()[index]->setMessage(text);

            } else {
                std::shared_ptr<Note> new_note = std::make_shared<Note>(QDateTime::currentDateTime(), text);
                plantGroup_->addNote(new_note);
            }
            setNoteList();
        }
        ui->addNoteButton->setText("Notiz hinzufügen");
        ui->noteEdit->hide();
        ui->notesListWidget->show();
        // gets set to the default value
        is_edit_ = false;
    }
}


void GroupDialog::on_notesListWidget_itemDoubleClicked(QListWidgetItem *item) {
    is_edit_ = true;
    on_addNoteButton_clicked();
    // Get the index of the clicked item
    int index = ui->notesListWidget->row(item);
    ui->noteEdit->setText(plantGroup_->getNotes()[index]->getMessage());
}

