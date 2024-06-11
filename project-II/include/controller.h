#pragma once

#include <string>

#include "trie.h"


// classe para gerenciar a Trie (construção, aplicação, etc)
class Controller {
public:
    Controller();
    ~Controller();

private:
    std::string readFile(const std::string& filename);

/* ----------------------------------
    métodos à serem determinados
---------------------------------- */

private:
    Trie trie;
};
