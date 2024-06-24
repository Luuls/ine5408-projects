#include <iostream>
#include <vector>

#include "trie.h"

Trie::Trie() : letter(0), dictPosition(0), lineLength(0) {
    for (int i = 0; i < 27; i++) {
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
            // recursivamente deleta os filhos
            delete children[i];
        }
    }
}

Trie::RetrievalResult Trie::retrieve(const std::string& word) {
    Trie* child = this;
    // navega até o nó que representa a última letra da palavra
    for (const auto& letter : word) {
        child = child->children[letter - 'a'];
        // se a palvra não existir, retorna (0, 0)
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
        this->getWords(words);
        return words;
    }

    Trie* child = this;
    if (prefix.size() > 1) {
        // navega até o nó que representa a penúltima letra do prefixo
        for (const auto& letter : prefix.substr(0, prefix.size() - 1)) {
            child = child->children[letter - 'a'];
            // se algum nó intermediário for nulo, significa
            // que o prefixo não existe dentro da trie
            if (child == nullptr) {
                return words;
            }
        }
    }

    char lastLetter = prefix.at(prefix.size() - 1);
    child = child->children[lastLetter - 'a'];
    if (child == nullptr) {
        return words;
    }

    // se o tamanho da linha do nó referente à
    // última letra do prefixo for diferente de 0,
    // então o prefixo também é uma palavra do dicionário
    if (child->lineLength != 0) {
        words.push_back(prefix);
    }

    // à partir do prefixo, recupera todas as palavras,
    // pois todas começam com `prefix`
    child->getWords(words, prefix);
    return words;
}

void Trie::getWords(std::vector<std::string>& words, std::string currentWord) {
    for (const auto& child : this->children) {
        if (child != nullptr) {
            std::string nextWord = currentWord + child->getLetter();
            // se o tamanho da linha do nó for diferente de 0,
            // então nextWord é uma palavra do dicionário
            if (child->getLineLength() != 0) {
                words.push_back(nextWord);
            }
            child->getWords(words, nextWord);
        }
    }
}

void Trie::insert(
                  const std::string& word,
                  unsigned int dictPosition,
                  unsigned int lineLength) {
    if (word.empty()) {
        return;
    }

    // a palavra inserida é consumida da esquerda para a direita
    // a cada chamada à insert, até que fique vazia
    char letter = word[0];
    size_t letterIndex = letter - 'a';
    auto& child = this->children[letterIndex];

    if (child == nullptr) {
        child = new Trie();
    }

    child->setLetter(letter);
    // se o tamanho da palavra for 1, o nó é a última letra da palavra original
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

void Trie::print(const std::string& prefix) {
    if (letter != 0) { // não imprime o caractere da raíz
        std::cout << prefix
            << letter
            << " (" << dictPosition << ", " << lineLength << ")\n";
    }
    for (auto child : children) {
        if (child) {
            child->print(prefix + "--");
        }
    }
}
