#pragma once

#include <vector>
#include <string>


/**
 * @class Trie
 * @brief Representa uma estrutura de dados trie para recuperação eficiente de palavras.
 *
 * A classe Trie fornece métodos para inserir palavras, recuperar palavras com um determinado prefixo
 * e imprimir o conteúdo da trie. Ela usa um array de ponteiros Trie para representar
 * os nós filhos e armazena informações sobre a letra, posição no dicionário
 * e comprimento da linha de cada nó.
 */
class Trie {
public:
    Trie();
    Trie(char letter, unsigned int dictPosition, unsigned int lineLength);
    ~Trie();

    // struct para facilitar a leitura do código
    struct RetrievalResult {
        unsigned int dictPosition;
        unsigned int lineLength;
    };

    /**
     * @brief Recupera todas as palavras com um determinado prefixo.
     * @param prefix O prefixo a ser procurado.
     * @return Um vetor contendo todas as palavras com o prefixo especificado.
     */
    std::vector<std::string> getWordsWithPrefix(const std::string& prefix);

    /**
     * @brief Recupera informações sobre uma palavra na trie.
     * @param word A palavra a ser recuperada.
     * @return Um objeto RetrievalResult contendo a posição da palavra no dicionário e o comprimento da linha.
     */
    RetrievalResult retrieve(const std::string& word);

    /**
     * @brief Insere uma palavra na trie.
     * @param word A palavra a ser inserida.
     * @param dictPosition A posição da palavra no dicionário.
     * @param lineLength O comprimento da linha da palavra.
     */
    void insert(const std::string& word, unsigned int dictPosition, unsigned int lineLength);

    void setLetter(char letter);
    char getLetter() const;

    void setDictPosition(unsigned int dictPosition);
    unsigned int getDictPosition() const;

    void setLineLength(unsigned int lineLength);
    unsigned int getLineLength() const;

    /**
     * @brief Imprime o conteúdo da trie.
     * @param prefix O prefixo a ser adicionado antes de cada palavra impressa.
     */
    void print(const std::string& prefix = "");

private:
    /**
     * @brief Recupera todas as palavras da trie de maneira recursiva.
     * @param words O vetor que armazena as palavras pertencentes ao dicionário.
     * @param currentWord A palavra construída com todos os nós ancestrais do atual.
     */
    void getWords(std::vector<std::string>& words, std::string currentWord = "");

private:
    Trie* children[26]; // array de Tries
    char letter;
    unsigned int dictPosition;
    unsigned int lineLength;
};
