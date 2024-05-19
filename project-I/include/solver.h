#ifndef SOLVER_H
#define SOLVER_H
#include <vector>
#include "array_stack.h"
#include "coordinate.h"

class Solver {
  public:
    static int solve(std::vector<std::vector<int>>& matrix, Coordinate robotPos);
};

#endif
