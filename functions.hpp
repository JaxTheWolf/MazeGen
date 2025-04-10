//
// Created by Roman Lubij on 8.4.25.
//

#ifndef FUNCTIONS_H
#define FUNCTIONS_H

int handleInput(int argc, char *argv[], int *xSize, int *ySize, int *seed);

void initGrid(int xSize, int ySize, std::vector<std::vector<Cell>> &grid);

void removeWalls(const Cell &firstCell, const Cell &secondCell, std::vector<std::vector<Cell>> &grid);

void generateMaze(int xSize, int ySize, std::vector<std::vector<Cell>> &grid);

void setEntranceAndExit(int xSize, int ySize, std::vector<std::vector<Cell> > &grid);

void generateSVG(int xSize, int ySize, const std::vector<std::vector<Cell>> &grid, const std::string &filename);

#endif //FUNCTIONS_H
