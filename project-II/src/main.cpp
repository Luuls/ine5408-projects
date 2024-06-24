#include <iostream>

#include "controller.h"


int main(int argc, char* argv[]) {
    std::string filename;
    std::cin >> filename;

    Controller controller;
    controller.buildTrie(filename);
    controller.problem1();

    return 0;
}
