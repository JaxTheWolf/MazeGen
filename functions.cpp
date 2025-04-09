//
// Created by Roman Lubij on 7.4.25.
//

#include <iostream>
#include <sstream>
#include <fstream>
#include <stack>

#include "Cell.hpp"
#include "functions.hpp"

///
/// @brief Populuje dimenze bludiště a náhodný seed.
/// @a Reference: https://stackoverflow.com/questions/2797813/how-to-convert-a-command-line-argument-to-int
/// @param argc Počet argumentů
/// @param argv Array argumentů
/// @param xSize Šířka bludiště
/// @param ySize Výška bludiště
/// @param seed Seed pro srand()
int handleInput(const int argc, char *argv[], int *xSize, int *ySize, int *seed) {
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
            std::cerr << "Nesprávný argument: " << argv[i] << " není číslo." << '\n';
        }
    }
    if (argc < 3) {
        std::cerr << "Použití: " << argv[0] << " <X buňek> <Y buňek> <srand() seed>" << '\n';
        return 1;
    }
    return 0;
}

///
/// @brief Připraví 2D vektor<Cell> a naplní jej.
/// @param xSize Šířka bludiště
/// @param ySize Výška bludiště
/// @param grid Mřížka buňek
void initGrid(const int xSize, const int ySize, std::vector<std::vector<Cell> > &grid) {
    // Musíme nastavit velikost vektoru v ose X
    grid.resize(xSize);
    for (int row = 0; row < xSize; row++) {
        // ... a také vektorů v ose Y
        grid.at(row).resize(ySize);
        for (int col = 0; col < ySize; col++) {
            // Zde se děje samosatatné plnění buňek
            grid.at(row).at(col) = Cell(col, row);
        }
    }
}

///
/// @brief Odstraní sousední stěny mezi 2 buňkami.
/// @a Reference: https://github.com/NacerKROUDIR/MazeGeneration/blob/main/Maze_Generator.py
/// @param firstCell První buňka
/// @param secondCell Druhá buňka
/// @param grid Mřížka buněk
void removeWalls(const Cell &firstCell, const Cell &secondCell, std::vector<std::vector<Cell> > &grid) {
    if (firstCell.x == secondCell.x) {
        // Buňky se nachází ve stejném sloupci
        if (firstCell.y < secondCell.y) {
            // Odstraníme spodek firstCell a vršek secondCell
            grid[firstCell.y][firstCell.x].walls.bottom = false;
            grid[secondCell.y][secondCell.x].walls.top = false;
        } else if (firstCell.y > secondCell.y) {
            // Odstraníme vršek firstCell a spodek secondCell
            grid[firstCell.y][firstCell.x].walls.top = false;
            grid[secondCell.y][secondCell.x].walls.bottom = false;
        }
    } else if (firstCell.y == secondCell.y) {
        // Buňky se nachází ve stejném řádku
        if (firstCell.x < secondCell.x) {
            // Odstraníme pravou stěnu firstCell a levou stěnu secondCell
            grid[firstCell.y][firstCell.x].walls.right = false; // Remove right wall of cell 1
            grid[secondCell.y][secondCell.x].walls.left = false; // Remove left wall of cell 2
        } else if (firstCell.x > secondCell.x) {
            // Odstraníme levou stěnu firstCell a pravou stěnu secondCell
            grid[firstCell.y][firstCell.x].walls.left = false;
            grid[secondCell.y][secondCell.x].walls.right = false;
        }
    }
}

///
/// @brief Tato funkce vygeneruje samotné bludiště; náhodně projde všechny buňky a vhodně jim nastaví stěny tak, aby vytvořili bludiště s aspoň jedním řešením.
/// @a Reference: https://github.com/NacerKROUDIR/MazeGeneration/blob/main/Maze_Generator.py
/// @param xSize Šířka bludiště
/// @param ySize Výška bludiště
/// @param grid Mřížka buňek
void generateMaze(const int xSize, const int ySize, std::vector<std::vector<Cell> > &grid) {
    std::stack<Cell *> stack;

    Cell *current = &grid.at(0).at(std::rand() % xSize); // NOLINT(cert-msc30-c, cert-msc50-cpp)
    current->visited = true;
    current->walls.top = false;
    stack.push(current);

    while (!stack.empty()) {
        current = stack.top();

        auto possibleNeighbor = current->checkNeighbors(xSize, ySize, grid);
        if (possibleNeighbor) {
            Cell *next = &grid.at(possibleNeighbor.value()->y).at(possibleNeighbor.value()->x);

            removeWalls(*current, *next, grid);

            next->visited = true;
            stack.push(next);
        } else {
            stack.pop();
        }
    }

    grid.at(ySize - 1).at(std::rand() % xSize).walls.bottom = false; // NOLINT(cert-msc30-c, cert-msc50-cpp)
}

///
/// @brief Vygeneruje SVG vyobrazení daného 2D vektoru<Cell>.
/// @a Reference: https://www.w3schools.com/graphics/svg_intro.asp a mnoho bolesti
/// @param xSize Šířka bludiště
/// @param ySize Výška bludiště
/// @param grid Mřížka buňek
/// @param filename Název výstupního souboru
void generateSVG(int xSize, int ySize, const std::vector<std::vector<Cell> > &grid, const std::string &filename) {
    constexpr int cellSize = 20; // Velikost každé buňky (px)
    constexpr int strokeWidth = 3; // Šířka stěn (px)
    const int width = xSize * cellSize + 2 * strokeWidth; // Šířka bludiště (px)
    const int height = ySize * cellSize + 2 * strokeWidth; // Výška bludiště (px)

    // Otevření výstupního souboru jako stream
    std::ofstream svgFile(filename);
    if (!svgFile.is_open()) {
        std::cerr << "Chyba: Nelze otevřít soubor  " << filename << " pro zápis." << '\n';
        return;
    }

    // Vypsání hlavičky SVG souboru
    svgFile << "<svg xmlns=\"http://www.w3.org/2000/svg\" ";
    svgFile << "width=\"" << width << "\" height=\"" << height << "\" ";
    svgFile << "viewBox=\"0 0 " << width << " " << height << "\">" << '\n';
    svgFile << "<rect width=\"" << width << "\" height=\"" << height << "\" fill=\"white\" />" << '\n';

    // Iterativně projdeme všechny buňky a vykreslíme jejich stěny
    for (int row = 0; row < ySize; ++row) {
        for (int col = 0; col < xSize; ++col) {
            const Cell &cell = grid[row][col];

            // Vypočítání souřadnic buňek v prostoru SVG
            int xPos = col * cellSize + strokeWidth;
            int yPos = row * cellSize + strokeWidth;

            // Kreslení vrchní stěnmy...
            if (cell.walls.top) {
                svgFile << "<line x1=\"" << xPos << "\" y1=\"" << yPos << "\" x2=\"" << (xPos + cellSize)
                        << "\" y2=\"" << yPos << "\" "
                        << "stroke=\"black\" stroke-width=\"" << strokeWidth << "\" />" << '\n';
            }

            // ... spodní stěny
            if (cell.walls.bottom) {
                svgFile << "<line x1=\"" << xPos << "\" y1=\"" << (yPos + cellSize) << "\" x2=\"" << (xPos + cellSize)
                        << "\" y2=\"" << (yPos + cellSize) << "\" "
                        << "stroke=\"black\" stroke-width=\"" << strokeWidth << "\" />" << '\n';
            }

            // ... levé stěny
            if (cell.walls.left) {
                svgFile << "<line x1=\"" << xPos << "\" y1=\"" << yPos << "\" x2=\"" << xPos << "\" y2=\""
                        << (yPos + cellSize) << "\" "
                        << "stroke=\"black\" stroke-width=\"" << strokeWidth << "\" />" << '\n';
            }

            // ... a pravé stěny
            if (cell.walls.right) {
                svgFile << "<line x1=\"" << (xPos + cellSize) << "\" y1=\"" << yPos << "\" x2=\"" << (xPos + cellSize)
                        << "\" y2=\"" << (yPos + cellSize) << "\" "
                        << "stroke=\"black\" stroke-width=\"" << strokeWidth << "\" />" << '\n';
            }
        }
    }

    // Uzavření streamu souboru
    svgFile << "</svg>" << '\n';
    svgFile.close();

    std::cout << "SVG soubor s bludištěm uložen do " << filename << '\n';
}
