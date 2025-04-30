#ifndef BOOK_H
#define BOOK_H

#include <string>

class Book {
public:
    int id;
    std::string title;
    std::string author;
    std::string content;
    bool isAvailable;

    Book(int id, const std::string& title, const std::string& author, const std::string& content = "")
        : id(id), title(title), author(author), content(content), isAvailable(true) {}

    void display() const;
};

#endif // BOOK_H
