//
// Created by jax on 8.4.25.
//

#ifndef FUNCTIONS_H
#define FUNCTIONS_H

void handleInput(const int argc, char *argv[], int *xSize, int *ySize, int *seed);

void initGrid(std::vector<std::vector<Cell>> &grid, const int xSize, const int ySize);

void removeWalls(const Cell &firstCell, const Cell &secondCell, std::vector<std::vector<Cell> > &grid);

void generateSVG(const std::vector<std::vector<Cell>> &grid, int mazeX, int mazeY, const std::string &filename);

#endif //FUNCTIONS_H
