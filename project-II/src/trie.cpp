#include <vector>

#include "../include/trie.h"

Trie::Trie() {
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
