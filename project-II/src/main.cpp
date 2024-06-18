#include "controller.h"


int main(int argc, char* argv[]) {
    Controller controller;
    controller.buildTrie(argv[1]);

    return 0;
}
