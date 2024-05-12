#ifndef NOTE_H
#define NOTE_H

#include <QString>
#include <QDateTime>

class Note {
    QDateTime creation_date_;
    QString message_;
public:
    Note(const QDateTime&  creation_date, const QString& message)
        : creation_date_(creation_date), message_(message) {}
    //void createNote(const QString&);
    QDateTime getDate() {return creation_date_;}
    QString getMessage() {return message_;}
    void setMessage(QString &message) {message_ = message;}
    void saveNoteToFile();
    void removeNote();
    Note* loadNotesFromFile(const QString&);

};

#endif // NOTE_H
