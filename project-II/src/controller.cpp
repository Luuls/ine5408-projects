#include <fstream>
#include <sstream>

#include "controller.h"


std::string Controller::readFile(const std::string& fileName) {
    std::ifstream file(fileName);
    std::stringstream buffer;
    std::string fileContent;

    // desta maneira, retorna o conteúdo do arquivo incluindo
    // os caracteres de quebra de linha ('\n')
    if (file.is_open()) {
        buffer << file.rdbuf();
        fileContent = buffer.str();
    }

    return fileContent;
}
