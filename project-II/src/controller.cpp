#include <fstream>
#include <sstream>
#include <iostream>

#include "controller.h"

Controller::Controller() {}

std::string Controller::readFile(const std::string& fileName) {
    std::ifstream file(fileName);
    std::stringstream buffer;
    std::string fileContent;

    // desta maneira, retorna o conteúdo do arquivo incluindo
    // os caracteres de quebra de linha ('\n')
    if (file.is_open()) {
        buffer << file.rdbuf();
        fileContent = buffer.str();
    }

    return fileContent;
}

void Controller::buildTrie(const std::string& filename) {
    std::string fileContent = this->readFile(filename);

    std::string::iterator mainIterator = fileContent.begin();
    // considerando que o arquivo sempre seja bem formado
    // e que todas as linhas comecem com '['
    while (mainIterator != fileContent.end()) {
        auto lineBegin = mainIterator;
        std::string word = this->readWord(mainIterator);
        while (*mainIterator != '\n') {
            mainIterator++;
        }

        std::size_t lineLength = mainIterator - lineBegin;
        std::size_t dictPosition = lineBegin - fileContent.begin();
        this->trie.insert(word, dictPosition, lineLength);
        mainIterator++; // vai para o início da linha seguinte
    }
}

std::string Controller::readWord(std::string::iterator& it) {
    std::string word{""};
    it++; // pula o '['
    while (*it != ']') {
        word += *it;
        it++;
    }
    return word;
}
