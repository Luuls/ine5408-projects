#pragma once

#include <array>
#include <vector>
#include <string>


class Trie {
public:
    Trie();
    ~Trie();

    struct RetrievalResult {
        bool found;
        unsigned int dictPosition;
        unsigned int lineLength;
    };

    RetrievalResult Retrieve(const std::string& word);

private:
    Trie* children; // array de Tries
    char letter;
    unsigned int dictPosition;
    unsigned int lineLength;
};
