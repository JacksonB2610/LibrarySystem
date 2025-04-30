#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <algorithm>
#include <string>
#include "Book.h"

std::unordered_set<std::string> stopWords = {
    "a", "an", "the", "and", "or", "but", "if", "while", "is", "was", "he", "she", "it", "they",
    "them", "of", "in", "on", "for", "with", "at", "by", "to", "from"
};

std::vector<std::string> tokenize(const std::string& text) {
    std::vector<std::string> tokens;
    std::string word;
    for (char c : text) {
        if (isalpha(c)) {
            word += tolower(c);
        } else if (!word.empty()) {
            if (stopWords.find(word) == stopWords.end()) {
                tokens.push_back(word);
            }
            word.clear();
        }
    }
    if (!word.empty() && stopWords.find(word) == stopWords.end()) {
        tokens.push_back(word);
    }
    return tokens;
}

std::string loadContentFromFile(const std::string& filename) {
    std::ifstream file(filename);
    std::stringstream buffer;
    if (file) {
        buffer << file.rdbuf();
        return buffer.str();
    } else {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return "";
    }
}

void generateTagCloud(const std::vector<Book>& books) {
    std::unordered_map<std::string, int> wordFreq;
    for (const auto& book : books) {
        std::vector<std::string> words = tokenize(book.content);
        for (const auto& word : words) {
            wordFreq[word]++;
        }
    }

    std::cout << "\n--- Tag Cloud (Top Words) ---\n";
    std::vector<std::pair<std::string, int>> sortedFreq(wordFreq.begin(), wordFreq.end());
    std::sort(sortedFreq.begin(), sortedFreq.end(), [](auto& a, auto& b) {
        return b.second < a.second;
    });

    int count = 0;
    for (const auto& pair : sortedFreq) {
        std::cout << pair.first << " (" << pair.second << "): ";
        int barLength = std::min(pair.second, 40); // max bar length
        std::cout << std::string(barLength, '*') << std::endl;
        if (++count >= 20) break; // limit output
    }
}

int main() {
    std::vector<Book> books;
    books.push_back(Book(1, "Physics 101", "John Doe", loadContentFromFile("data/physics.txt")));
    books.push_back(Book(2, "Chemistry for Beginners", "Jane Smith", loadContentFromFile("data/chemistry.txt")));
    books.push_back(Book(3, "Shakespeare's Works", "William Shakespeare", loadContentFromFile("data/literature.txt")));
    // Add more books as needed

    generateTagCloud(books);

    return 0;
}
