#ifndef NOTE_H
#define NOTE_H

#include <string>
#include <chrono>

class Note {
    std::chrono::system_clock::time_point creation_date_;
    std::string message_;
public:
    Note(const std::chrono::system_clock::time_point&  creation_date, const std::string& message)
        : creation_date_(creation_date), message_(message) {}

    // For testing
    Note() = default;

    std::chrono::system_clock::time_point getDate() {return creation_date_;}
    std::string getMessage() {return message_;}
    void setMessage(std::string &message) {message_ = message;}
    //Needs implementation
    Note* loadNotesFromFile(const std::string&);

};

#endif // NOTE_H
