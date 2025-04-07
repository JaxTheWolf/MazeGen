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
    bool visited;
    bool solution;
    int x, y;
    wallsOrPath walls;
    wallsOrPath path;

    static std::optional<Cell> findCell(const std::vector<Cell> &grid, const int x, const int y) {
        for (const std::optional<Cell> cell: grid) {
            if (cell && (cell->x == x && cell->y == y)) {
                return cell;
            }
        }
        return std::nullopt;
    }

    auto checkNeighbors(const std::vector<Cell> &grid) const {
        // NOLINT(*-use-nodiscard)
        std::vector<Cell> neighbors;
        std::optional<Cell> top{}, bottom{}, left{}, right{};
        if (this->y - 1 >= 0 && this->y - 1 < grid.size() - 1) {
            top = findCell(grid, this->x, this->y - 1);
        }
        if (this->y + 1 < grid.size() - 1) {
            bottom = findCell(grid, this->x, this->y + 1);
        }
        if (this->x - 1 >= 0 && this->x - 1 < grid.size() - 1) {
            left = findCell(grid, this->x - 1, this->y);
        }
        if (this->y + 1 < grid.size() - 1) {
            right = findCell(grid, this->x + 1, this->y);
        }

        if (top && !top->visited) neighbors.push_back(*top);
        if (bottom && !bottom->visited) neighbors.push_back(*bottom);
        if (left && !left->visited) neighbors.push_back(*left);
        if (right && !right->visited) neighbors.push_back(*right);

        for (auto cell: neighbors) {
            std::cout << cell.x << ", " << cell.y << std::endl;
        }

        return neighbors[std::rand() % neighbors.size()]; // NOLINT(cert-msc30-c, cert-msc50-cpp)
    }
};


#endif //CELL_H
