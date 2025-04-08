#include <cstdlib>
#include <iostream>
#include <optional>
#include <vector>
#include <stack>

#include "Cell.h"
#include "functions.h"

#define endl '\n'

int main(const int argc, char *argv[]) {
  int maze_x = 0, maze_y = 0, randSeed = 0;
  bool flag = true;

  std::vector<Cell> grid;
  // Načtení hodnot z argv to jhednotlivých proměnných s type checking
  handleInput(argc, argv, &maze_x, &maze_y, &randSeed);
  // Vytvoření gridu objektů Cell
  initGrid(grid, maze_x, maze_y);
  // nastavení srand() seedu
  std::srand(randSeed);

  // Proměnné pro algoritmus
  std::stack<Cell> solution, stack;
  Cell nextCell{}, currentCell = grid[0];
}

