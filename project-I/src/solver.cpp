#include "../include/solver.h"

int Solver::solve(std::vector<std::vector<int>>& matrix, Coordinate robotPos) {
    if (matrix[robotPos.x][robotPos.y] == 0) {
        return 0;
    }

    int height = matrix.size();
    int width = matrix[0].size();

    ArrayStack<Coordinate> cellsToVisit(2350);

    matrix[robotPos.x][robotPos.y] = 0;
    int totalArea = 1;

    Coordinate offsets[] = { {0, -1}, {-1, 0}, {0, 1}, {1, 0} };
    while (true) {
        for (const auto& offset : offsets) {
            Coordinate newPos = {robotPos.x + offset.x, robotPos.y + offset.y};
            if (newPos.x < 0 || newPos.x >= height || newPos.y < 0 || newPos.y >= width) {
                continue;
            }
            if (matrix[newPos.x][newPos.y] == 1) {
                // marca a posição empilhada como 0 para não ser empilhada novamente
                // futuramente
                matrix[newPos.x][newPos.y] = 0;
                totalArea++;
                cellsToVisit.push(newPos);
            }
        }

        if (cellsToVisit.empty()) {
            return totalArea;
        }

        robotPos = cellsToVisit.pop();
    }
}
