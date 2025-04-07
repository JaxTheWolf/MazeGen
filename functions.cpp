//
// Created by jax on 7.4.25.
//

#include "Cell.h"

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
