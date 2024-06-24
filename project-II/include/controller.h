#pragma once

#include <string>

#include "trie.h"


// classe para gerenciar a Trie (construção, aplicação, etc)
class Controller {
public:
    Controller();

    void buildTrie(const std::string& filename);

    Trie& getTrie();

    void handleInput();

private:
    std::string readFile(const std::string& filename);
    std::string readWord(std::string::iterator& it);

private:
    Trie trie;
};
