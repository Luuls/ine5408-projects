#pragma once

#include <iostream>
#include <vector>
#include <string>


class Trie {
public:
    Trie();
    Trie(char letter, unsigned int dictPosition, unsigned int lineLength);
    ~Trie();

    struct RetrievalResult {
        bool found;
        unsigned int dictPosition;
        unsigned int lineLength;
    };

    std::vector<std::string> getWordsWithPrefix(const std::string& prefix);

    RetrievalResult retrieve(const std::string& word);

    void insert(const std::string& word, unsigned int dictPosition, unsigned int lineLength);

    void setLetter(char letter);
    char getLetter() const;

    void setDictPosition(unsigned int dictPosition);
    unsigned int getDictPosition() const;

    void setLineLength(unsigned int lineLength);
    unsigned int getLineLength() const;

    void print(const std::string& prefix = "") {
        if (letter != 0) { // Avoid printing the root node's letter
            std::cout << prefix << letter << " (" << dictPosition << ", " << lineLength << ")\n";
        }
        for (auto child : children) {
            if (child) {
                child->print(prefix + "--");
            }
        }
    }

private:
    void getWords( std::string currentWord, std::vector<std::string>& words);

private:
    Trie* children[26]; // array de Tries
    char letter;
    unsigned int dictPosition;
    unsigned int lineLength;
};
