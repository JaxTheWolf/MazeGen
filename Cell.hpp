//
// Created by jax on 7.4.25.
//

#ifndef CELL_H
#define CELL_H

#include <cstdlib>
#include <iostream>
#include <optional>
#include <vector>

struct wallsOrPath {
    bool top;
    bool bottom;
    bool left;
    bool right;
};

class Cell {
public:
    bool visited, solution;
    wallsOrPath walls, path;
    int x, y;

    explicit Cell(int xCoord = 0, int yCoord = 0)
        : visited(false), solution(false), walls({true, true, true, true}), path({false, false, false, false}),
          x(xCoord),
          y(yCoord) {
        std::cout << "Cell created at (" << x << ", " << y << ")\n";
    }

    ~Cell() {
        std::cout << "Cell (" << x << ", " << y << ") destroyed\n";
    }


    std::optional<Cell *> checkNeighbors(const std::vector<std::vector<Cell> > &grid, const int xSize,
                                         const int ySize) {
        std::vector<Cell *> neighbors;

        // Top neighbor
        if (y - 1 >= 0) {
            Cell *top = const_cast<Cell *>(&grid[x][y - 1]);
            std::cout << "Top neighbor: " << top->x << ", " << top->y << std::endl;
            if (!top->visited) {
                neighbors.push_back(top);
            }
        }

        // Bottom neighbor
        if (y + 1 < ySize) {
            Cell *bottom = const_cast<Cell *>(&grid[x][y + 1]);
            std::cout << "Bottom neighbor: " << bottom->x << ", " << bottom->y << std::endl;
            if (!bottom->visited) {
                neighbors.push_back(bottom);
            }
        }

        // Left neighbor
        if (x - 1 >= 0) {
            Cell *left = const_cast<Cell *>(&grid[x - 1][y]);
            std::cout << "Left neighbor: " << left->x << ", " << left->y << std::endl;
            if (!left->visited) {
                neighbors.push_back(left);
            }
        }

        // Right neighbor
        if (x + 1 < xSize) {
            Cell *right = const_cast<Cell *>(&grid[x + 1][y]);
            std::cout << "Right neighbor: " << right->x << ", " << right->y << std::endl;
            if (!right->visited) {
                neighbors.push_back(right);
            }
        }

        // Return a random unvisited neighbor if any found
        if (!neighbors.empty()) {
            return neighbors[std::rand() % neighbors.size()];
        }
        return std::nullopt; // No unvisited neighbors found
    }
};


#endif //CELL_H
