#include <iostream>

#include "controller.h"


int main() {
    std::string filename;
    std::cin >> filename;

    Controller controller;
    controller.buildTrie(filename);
    controller.handleInput();

    return 0;
}
