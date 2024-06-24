#pragma once

#include <string>

#include "trie.h"


/**
 * @class Controller
 * @brief Controla a leitura do arquivo de dicionário e a interação com o usuário.
 *
 * A classe Controller lê o conteúdo de um arquivo de dicionário e insere as palavras
 * na trie. Ela também lê palavras do console e imprime informações sobre elas,
 * como descrito no enunciado.
 */
class Controller {
public:
    Controller();

    /**
     * @brief Lê o conteúdo de um arquivo de dicionário e
     * insere as palavras na trie.
     * @param filename O nome do arquivo a ser lido.
     */
    void buildTrie(const std::string& filename);

    Trie& getTrie();

    /**
     * @brief Lê palavras do console e imprime informações sobre elas,
     * como descrito no enunciado.
     */
    void handleInput();

private:
    // métodos auxiliares
    std::string readFile(const std::string& filename);
    std::string readWord(std::string::iterator& it);

private:
    Trie trie;
};
