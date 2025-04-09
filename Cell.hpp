//
// Created by Roman Lubij on 7.4.25.
//

#ifndef CELL_H
#define CELL_H

#include <cstdlib>
#include <iostream>
#include <optional>
#include <vector>

///
/// @brief Struktura pro zjednodušení práce se stěnami buněk.
/// @param top Vrchní stěna
/// @param bottom Spodní stěna
/// @param left levá stěna
/// @param right pravá stěna
struct wallStruct {
    bool top;
    bool bottom;
    bool left;
    bool right;
};

///
/// @class Cell
/// @a Reference: https://en.cppreference.com/w/cpp/language/class
/// @brief Třída, popisující 1 buňku bludiště.
/// @param xCoord X-ový komponent souřadnice buňky
/// @param yCoord Y-ový komponent souřadnice buňky
class Cell {
public:
    bool visited;
    wallStruct walls;
    int x, y;

    explicit Cell(int xCoord = 0, int yCoord = 0)
        : visited(false), walls({true, true, true, true}),
          x(xCoord),
          y(yCoord) {
    }

    ///
    /// @brief Nalezne sousední buňky kolem buňky[xSize, ySize] a vrátí z nich jednou, náhodně.
    /// @param xSize Šířka bludiště
    /// @param ySize Výška bludiště
    /// @param grid Mřížka buňek
    /// @return Cell* NEBO std::nullopt
    std::optional<Cell *> checkNeighbors(const int xSize, const int ySize,
                                         const std::vector<std::vector<Cell> > &grid) {
        std::vector<Cell *> neighbors;

        // Vrchní soused
        if (y - 1 >= 0) {
            Cell *top = const_cast<Cell *>(&grid.at(y - 1).at(x));
            if (!top->visited) {
                neighbors.push_back(top);
            }
        }

        // Spodní soused
        if (y + 1 < ySize) {
            Cell *bottom = const_cast<Cell *>(&grid.at(y + 1).at(x));
            if (!bottom->visited) {
                neighbors.push_back(bottom);
            }
        }

        // Levý soused
        if (x - 1 >= 0) {
            Cell *left = const_cast<Cell *>(&grid.at(y).at(x - 1));
            if (!left->visited) {
                neighbors.push_back(left);
            }
        }

        // Pravý soused
        if (x + 1 < xSize) {
            Cell *right = const_cast<Cell *>(&grid.at(y).at(x + 1));
            if (!right->visited) {
                neighbors.push_back(right);
            }
        }

        // Pokud byli sousedi nalezeni, vrať náíhodného z neighbors
        if (!neighbors.empty()) {
            return neighbors[std::rand() % neighbors.size()];
        }
        // ... pokud ne, nullopt
        return std::nullopt;
    }
};


#endif //CELL_H
