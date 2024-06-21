<<<<<<< Updated upstream
#include <iostream>
#include <sstream>
#include <fstream>
#include <iterator>

=======
>>>>>>> Stashed changes
#include "trie.h"
#include "controller.h"


int main(int argc, char* argv[]) {
    Controller controller;
    controller.buildTrie(argv[1]);
    Trie& trie = controller.getTrie();
    trie.print();

    return 0;
}
