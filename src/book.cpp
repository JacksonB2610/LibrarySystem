#include "Book.h"
#include <iostream>

void Book::display() const {
    std::cout << "ID: " << id << ", Title: " << title << ", Author: " << author
              << ", Status: " << (isAvailable ? "Available" : "Borrowed") << std::endl;
}

