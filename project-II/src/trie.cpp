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
    Trie* child = this;
    for (const auto& letter : word) {
        child = child->children[letter - 'a'];
        if (child == nullptr) {
            return { 0, 0 };
        }
    }

    return { child->getDictPosition(), child->getLineLength() };
}

std::vector<std::string> Trie::getWordsWithPrefix(const std::string& prefix) {
    std::vector<std::string> words;

    if (prefix.empty()) {
        // define-se que a string vazia é prefixo de qualquer palavra
        // portanto, a Trie retorna todas as suas palavras
        this->getWords("", words);
        return words;
    }

    Trie* child = this;
    if (prefix.size() > 1) {
        for (const auto& letter : prefix.substr(0, prefix.size() - 1)) {
            child = child->children[letter - 'a'];
            if (child == nullptr) {
                return words;
            }
        }
    }

    char lastLetter = prefix.at(prefix.size() - 1);
    child = child->children[lastLetter - 'a'];
    if (child != nullptr) {
        if (child->lineLength != 0) {
            words.push_back(prefix);
        }
    }
    else {
        return words;
    }

    child->getWords(prefix, words);
    return words;
}

void Trie::getWords(std::string currentWord, std::vector<std::string>& words) {
    for (const auto& child : this->children) {
        if (child != nullptr) {
            std::string nextWord = currentWord + child->getLetter();
            if (child->getLineLength() != 0) {
                words.push_back(nextWord);
            }
            child->getWords(nextWord, words);
        }
    }
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

    child->insert(word.substr(1), dictPosition, lineLength);
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
