//
// Created by jax on 7.4.25.
//

#ifndef FUNCTIONS_H
#define FUNCTIONS_H

void handleInput(int argc, char *argv[], int* xSize, int* ySize, int* seed);

void removeWalls(Cell &current, Cell &next);

void addSolutionPath(Cell &previous, Cell &current);

void initGrid(std::vector<Cell> &grid, int xSize, int ySize);

#endif //FUNCTIONS_H
