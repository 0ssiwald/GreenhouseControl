#ifndef NOTE_H
#define NOTE_H

#include <string>
#include <chrono>


class Note {
    std::chrono::system_clock::time_point creation_date;
    std::string message;
public:
    Note();
    void createNote(const std::string&);
    void saveNoteToFile();
    void removeNote();
    Note* loadNotesFromFile(const std::string&);
    std::string displayNote();
};

#endif // NOTE_H
