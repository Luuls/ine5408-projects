#pragma once

#include <string>
#include <iostream>
#include <vector>

#include "trie.h"

// talvez essa classe seja apagada

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
