#include <vector>

#include "../include/trie.h"

Trie::Trie() : letter(0), dictPosition(0), lineLength(0) {
    for (int i = 0; i < 26; i++) {
        children[i] = nullptr;
    }
}

Trie::Trie(char letter, unsigned int dictPosition, unsigned int lineLength) :
        letter(letter), dictPosition(dictPosition), lineLength(lineLength) {

    for (int i = 0; i < 26; i++) {
        this->children[i] = nullptr;
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

void Trie::insert(const std::string& word, unsigned int dictPosition, unsigned int lineLength) {
    if (word.empty()) {
        return;
    }

    char letter = word[0];
    size_t letterIndex = letter - 'a';
    auto& child = this->children[letterIndex];

    if (child == nullptr) {
        child = new Trie();
    }

    child->setLetter(letter);
    if (word.size() == 1) {
        child->setDictPosition(dictPosition);
        child->setLineLength(lineLength);
    }
    else {
        child->insert(word.substr(1), dictPosition, lineLength);
    }
}

void Trie::setLetter(char letter) { this->letter = letter; }
char Trie::getLetter() const { return this->letter; }

void Trie::setDictPosition(unsigned int dictPosition) {
    this->dictPosition = dictPosition;
}
unsigned int Trie::getDictPosition() const { return this->dictPosition; }

void Trie::setLineLength(unsigned int lineLength) {
    this->lineLength = lineLength;
}
unsigned int Trie::getLineLength() const { return this->lineLength; }
