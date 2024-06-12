#pragma once

#include <array>
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

private:
    Trie* children[26]; // array de Tries
    char letter;
    unsigned int dictPosition;
    unsigned int lineLength;
};
