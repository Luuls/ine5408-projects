#pragma once

#include <string>

#include "trie.h"


// classe para gerenciar a Trie (construção, aplicação, etc)
class Controller {
public:
    Controller();

    void buildTrie(const std::string& filename);

    Trie& getTrie() { return this->trie; }

    void buildTrie(const std::string& filename);

private:
    std::string readFile(const std::string& filename);
    std::string readWord(std::string::iterator& it);

/* ----------------------------------
    métodos à serem determinados
---------------------------------- */

private:
    Trie trie;
};
