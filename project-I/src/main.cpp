// Copyright [2024] <Caio César Rodrigues de Aquino, Luan da Silva Moraes>

#include <cstdint> // std::size_t
#include <fstream>
#include <iostream>
#include <istream>
#include <iterator>
#include <stdexcept> // C++ exceptions
#include <string>
#include <vector>

#include "../include/array_stack.h"
#include "../include/xml_tree.h"
#include "../include/xml_parser.h"
#include "../include/coordinate.h"
#include "../include/solver.h"


int main(int argc, char* argv[]) {
    if (argc == 1) {
        std::cerr << "Usage: " << argv[0] << " <xml_path>\n";
        return 1;
    }

    std::string xmlPath = argv[1];
    XmlTree xml;
    try {
        xml = XmlParser::parse(xmlPath);
    }
    catch (const std::runtime_error& e) {
        std::cout << "erro\n";
        return 0;
    }

    for (auto& scenario : xml["cenario"]) {
        int width = std::stoi(scenario["dimensoes"][0]["largura"][0].getContent());
        int height = std::stoi(scenario["dimensoes"][0]["altura"][0].getContent());

        // a matriz vem do xml como uma string unidimensional.
        // Portanto, transforma-se-a em uma matriz bidimensional antes de
        // computar a área varrida pelo robô
        std::string xmlMatrix = scenario["matriz"][0].getContent();
        std::vector<std::vector<int>> matrix(height);
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                matrix[i].push_back(xmlMatrix[i * width + j] - '0');
            }
        }

        int robotX = std::stoi(scenario["robo"][0]["x"][0].getContent());
        int robotY = std::stoi(scenario["robo"][0]["y"][0].getContent());
        Coordinate robotPos = {robotX, robotY};

        int totalArea = Solver::solve(matrix, robotPos);
        std::cout << scenario["nome"][0].getContent() << " " << totalArea << '\n';
    }

    return 0;
}
