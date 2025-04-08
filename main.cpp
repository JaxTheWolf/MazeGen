#include <cstdlib>
#include <iostream>
#include <vector>

#include "Cell.hpp"
#include "functions.hpp"

#define endl '\n'

// T0DO: Make the coordinate systems concise. Something isn't right (cell.h)

///
/// @brief "entrypoint" našeho programu
/// @param argc počet argumentů
/// @param argv argumenty samotné
/// @return int (0/1)
int main(const int argc, char *argv[]) {
  int maze_x = 0, maze_y = 0, randSeed = 0;

  // Načtení hodnot z argv do jednotlivých proměnných s type checking
  if (handleInput(argc, argv, &maze_x, &maze_y, &randSeed)) {
    // Něco nebylo dle očekávání, program se ukončí v chybném stavu
    return 1;
  }
  // Vytvoření a iniciální populace 2D vektoru objektů Cell
  std::vector<std::vector<Cell>> grid;
  initGrid(maze_x, maze_y, grid);
  // nastavení srand() seedu
  std::srand(randSeed);

  // Samotné generování bludiště pomocí DFS
  generateMaze(maze_x, maze_y, grid);
  // Následovné generování výstupního SVG
  generateSVG(maze_x, maze_y, grid, "maze.svg");
}

