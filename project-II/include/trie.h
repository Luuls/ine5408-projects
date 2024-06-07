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

    std::vector<std::string> getWordsWithPrefix(const std::string& prefix);
    RetrievalResult retrieve(const std::string& word);

private:
    Trie* children[26]; // array de Tries
    char letter;
    unsigned int dictPosition;
    unsigned int lineLength;
};
