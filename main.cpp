#include <cstdlib>
#include <iostream>
#include <optional>
#include <vector>
#include <stack>

#include "Cell.hpp"
#include "functions.hpp"

#define endl '\n'

int main(const int argc, char *argv[]) {
  int maze_x = 0, maze_y = 0, randSeed = 0;
  bool flag = true;

  std::vector<std::vector<Cell> > grid;

  // Načtení hodnot z argv to jhednotlivých proměnných s type checking
  handleInput(argc, argv, &maze_x, &maze_y, &randSeed);
  // Vytvoření gridu objektů Cell
  initGrid(grid, maze_x, maze_y);
  // nastavení srand() seedu
  std::srand(randSeed);

  std::stack<Cell *> stack;

  Cell *current = &grid.at(0).at(0);
  current->visited = true;
  stack.push(current);

  std::cout << rand() << endl;
  std::cout << rand() << endl;

  while (!stack.empty()) {
    current = stack.top();

    auto possibleNeighbor = current->checkNeighbors(grid, maze_x, maze_y);
    if (possibleNeighbor) {
      Cell *next = &grid.at(possibleNeighbor.value()->x).at(possibleNeighbor.value()->y);

      removeWalls(*current, *next, grid);

      next->visited = true;
      stack.push(next);
    } else {
      stack.pop();
    }
  }


  generateSVG(grid, maze_x, maze_y, "maze.svg");
}

