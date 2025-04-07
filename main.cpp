#include <cstdlib>
#include <iostream>
#include <optional>
#include <vector>
#include <stack>
#include <sstream>

#include "Cell.h"
#include "functions.h"

#define endl '\n'

int main(int argc, char *argv[]) {
  int maze_x, maze_y, randSeed = 0;
  bool flag = true;

  if (argc < 3) {
    std::cerr << "Usage: " << argv[0] << " <X cells> <Y Cells> <srand() seed>" << endl;
    return 1;
  }

  for (int i = 1; i < argc; ++i) {
    std::istringstream iss(argv[i]);
    int number;
    if (iss >> number) {
      switch (i) {
        case 1:
          maze_x = number;
          break;
        case 2:
          maze_y = number;
          break;
        case 3:
          randSeed = number;
          break;
        default: ;
      }
    } else {
      std::cerr << "Invalid argument: " << argv[i] << " is not an integer." << endl;
    }
  }

  std::srand(randSeed);

  std::vector<Cell> grid;

  for (int i = 0; i < maze_x; i++) {
    for (int j = 0; j < maze_y; j++) {
      Cell cell{};
      cell.x = i;
      cell.y = j;
      cell.walls.top = cell.walls.bottom = cell.walls.left = cell.walls.right =
                                                             true;
      cell.path.top = cell.path.bottom = cell.path.left = cell.path.right =
                                                          false;

      if (i == 1 && j == 2) {
        cell.solution = true;
        cell.visited = true;
      } else {
        cell.solution = cell.visited = false;
      }
      grid.push_back(cell);
    }
  }

  std::stack<Cell> stack;
  std::stack<Cell> solution;

  Cell currentCell = grid[0];
  std::optional nextCell = currentCell.checkNeighbors(grid);

  do {
    currentCell.visited = true;
    if (nextCell.has_value()) {
      nextCell->visited = true;
      stack.push(nextCell.value());
      removeWalls(currentCell, nextCell.value());
      currentCell = nextCell.value();
      if (flag) {
        solution.push(currentCell);
      }
    } else if (!stack.empty()) {
      if (currentCell.x == maze_x - 1 && currentCell.y == maze_y - 1) {
        flag = false;
      }
      if (flag) {
        solution.pop();
      }
    } else {
      if (!solution.empty()) {
        Cell previousCell = currentCell;
        currentCell = solution.top();
        currentCell.solution = true;
        addSolutionPath(previousCell, currentCell);
        solution.pop();
      } else {
        Cell previousCell = currentCell;
        currentCell = grid[0];
        addSolutionPath(previousCell, currentCell);
      }
    }
  } while (nextCell.has_value());
}

