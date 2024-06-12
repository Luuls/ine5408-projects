#include <vector>

#include "../include/trie.h"

Trie::Trie() : letter(0), dictPosition(0), lineLength(0) {
    for (int i = 0; i < 26; i++) {
        children[i] = nullptr;
    }
}

Trie::~Trie() {
    for (int i = 0; i < 26; i++) {
        if (children[i] != nullptr) {
            delete children[i];
        }
    }
}

Trie::RetrievalResult Trie::retrieve(const std::string& word) {
}

std::vector<std::string> Trie::getWordsWithPrefix(const std::string& prefix) {
}
