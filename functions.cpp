//
// Created by jax on 7.4.25.
//

#include <sstream>
#include <fstream>

#include "Cell.hpp"
#include "functions.hpp"

void handleInput(const int argc, char *argv[], int *xSize, int *ySize, int *seed) {
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

void initGrid(std::vector<std::vector<Cell>> &grid, const int xSize, const int ySize) {
    grid.resize(xSize);
    for (int i = 0; i < xSize; i++) {
        grid.at(i).resize(ySize);
        // std::cout << "Initializing row " << i << " of " << xSize << "..." << std::endl;
        for (int j = 0; j < ySize; j++) {
            Cell cell;
            cell.x = i;
            cell.y = j;
            grid.at(i).at(j) = cell;
            // std::cout << "Initializing cell " << i << "," << j << " of " << xSize << "x" << ySize << "..." << std::endl;
        }
    }
    // std::cout << "Grid of size " << grid.size() << " ready" << std::endl;
}

void removeWalls(const Cell &firstCell, const Cell &secondCell, std::vector<std::vector<Cell> > &grid) {
    if (firstCell.x == secondCell.x) {
        // Same column
        if (firstCell.y < secondCell.y) {
            grid[firstCell.y][firstCell.x].walls.bottom = false; // Remove bottom wall of cell 1
            grid[secondCell.y][secondCell.x].walls.top = false; // Remove top wall of cell 2
        } else if (firstCell.y > secondCell.y) {
            grid[firstCell.y][firstCell.x].walls.top = false; // Remove top wall of cell 1
            grid[secondCell.y][secondCell.x].walls.bottom = false; // Remove bottom wall of cell 2
        }
    } else if (firstCell.y == secondCell.y) {
        // Same row
        if (firstCell.x < secondCell.x) {
            grid[firstCell.y][firstCell.x].walls.right = false; // Remove right wall of cell 1
            grid[secondCell.y][secondCell.x].walls.left = false; // Remove left wall of cell 2
        } else if (firstCell.x > secondCell.x) {
            grid[firstCell.y][firstCell.x].walls.left = false; // Remove left wall of cell 1
            grid[secondCell.y][secondCell.x].walls.right = false; // Remove right wall of cell 2
        }
    }
}

void addSolutionPath(const Cell &firstCell, const Cell &secondCell, std::vector<std::vector<Cell> > &grid) {
    grid[firstCell.y][firstCell.x].path.bottom = (firstCell.y < secondCell.y); // Example: Set directions based on relative positions
    grid[firstCell.y][firstCell.x].path.right = (firstCell.x < secondCell.x);
    grid[secondCell.y][secondCell.x].path.top = (secondCell.y < firstCell.y);
    grid[secondCell.y][secondCell.x].path.left = (secondCell.x < firstCell.x);
}

void generateSVG(const std::vector<std::vector<Cell> > &grid, int mazeX, int mazeY, const std::string &filename) {
    constexpr int cellSize = 20; // Size of each cell (in pixels) in the SVG output
    constexpr int strokeWidth = 2; // Thickness of the walls
    const int width = mazeX * cellSize; // Width of the maze in pixels
    const int height = mazeY * cellSize; // Height of the maze in pixels

    // Open the output SVG file
    std::ofstream svgFile(filename);
    if (!svgFile.is_open()) {
        std::cerr << "Error: Could not open file " << filename << " for writing." << std::endl;
        return;
    }

    // Write the SVG header
    svgFile << "<svg xmlns=\"http://www.w3.org/2000/svg\" ";
    svgFile << "width=\"" << width << "\" height=\"" << height << "\" ";
    svgFile << "viewBox=\"0 0 " << width << " " << height << "\">" << std::endl;
    svgFile << "<rect width=\"" << width << "\" height=\"" << height << "\" fill=\"white\" />" << std::endl;

    // Iterate through the grid and draw walls for each cell
    for (int y = 0; y < mazeY; ++y) {
        for (int x = 0; x < mazeX; ++x) {
            const Cell &cell = grid[y][x];

            // Calculate the cell's top-left corner in SVG coordinate space
            int xPos = x * cellSize;
            int yPos = y * cellSize;

            // Draw the top wall
            if (cell.walls.top) {
                svgFile << "<line x1=\"" << xPos << "\" y1=\"" << yPos << "\" x2=\"" << (xPos + cellSize)
                        << "\" y2=\"" << yPos << "\" "
                        << "stroke=\"black\" stroke-width=\"" << strokeWidth << "\" />" << std::endl;
            }

            // Draw the bottom wall
            if (cell.walls.bottom) {
                svgFile << "<line x1=\"" << xPos << "\" y1=\"" << (yPos + cellSize) << "\" x2=\"" << (xPos + cellSize)
                        << "\" y2=\"" << (yPos + cellSize) << "\" "
                        << "stroke=\"black\" stroke-width=\"" << strokeWidth << "\" />" << std::endl;
            }

            // Draw the left wall
            if (cell.walls.left) {
                svgFile << "<line x1=\"" << xPos << "\" y1=\"" << yPos << "\" x2=\"" << xPos << "\" y2=\""
                        << (yPos + cellSize) << "\" "
                        << "stroke=\"black\" stroke-width=\"" << strokeWidth << "\" />" << std::endl;
            }

            // Draw the right wall
            if (cell.walls.right) {
                svgFile << "<line x1=\"" << (xPos + cellSize) << "\" y1=\"" << yPos << "\" x2=\"" << (xPos + cellSize)
                        << "\" y2=\"" << (yPos + cellSize) << "\" "
                        << "stroke=\"black\" stroke-width=\"" << strokeWidth << "\" />" << std::endl;
            }
        }
    }

    // Close the SVG
    svgFile << "</svg>" << std::endl;
    svgFile.close();

    std::cout << "Maze SVG generated and saved to " << filename << std::endl;
}
