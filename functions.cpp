//
// Created by jax on 7.4.25.
//

#include <sstream>

#include "Cell.h"

void handleInput(const int argc, char *argv[], int* xSize, int* ySize, int* seed) {
    for (int i = 1; i < argc; ++i) {
        std::istringstream iss(argv[i]);
        if (int number; iss >> number) {
            switch (i) {
                case 1:
                    *xSize = number;
                break;
                case 2:
                    *ySize = number;
                break;
                case 3:
                    *seed = number;
                break;
                default: ;
            }
        } else {
            std::cerr << "Invalid argument: " << argv[i] << " is not an integer." << std::endl;
        }
    }
    if (argc < 3) {
        std::cerr << "Usage: " << argv[0] << " <X cells> <Y Cells> <srand() seed>" << std::endl;
    }
}

void initGrid(std::vector<Cell>& grid, const int xSize, const int ySize) {
    for (int i = 0; i < xSize; i++) {
        for (int j = 0; j < ySize; j++) {
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
    std::cout << "Grid of size " << grid.size() << " ready" << std::endl;
}

void removeWalls(Cell &current, Cell &next) {
    const int dx = current.x - next.x;
    const int dy = current.y - next.y;
    if (dx == 1) {
        current.walls.left = false;
        next.walls.right = false;
    }
    if (dx == -1) {
        current.walls.right = false;
        next.walls.right = false;
    }
    if (dy == 1) {
        current.walls.top = false;
        next.walls.bottom = false;
    }
    if (dy == -1) {
        current.walls.bottom = false;
        next.walls.top = false;
    }
}

void addSolutionPath(Cell &previous, Cell &current) {
    const int dx = current.x - previous.x;
    const int dy = current.y - previous.y;
    if (dx == 1) {
        current.path.left = true;
        previous.path.right = true;
    }
    if (dx == -1) {
        current.path.right = true;
        previous.path.left = true;
    }
    if (dy == 1) {
        current.path.top = true;
        previous.path.bottom = true;
    }
    if (dy == -1) {
        current.path.bottom = true;
        previous.path.top = true;
    }
}
