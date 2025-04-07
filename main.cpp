#include <cstdlib>
#include <iostream>
#include <vector>

#define endl '\n'

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
  unsigned int x, y;
  wallsOrPath walls;
  wallsOrPath path;

  static auto findCell(const std::vector<Cell> &grid, const unsigned int x, const unsigned int y) {
    const unsigned long index = grid.size() - (x + y) - 1;
    if (grid.size() >= x + y) return grid[index];
    else return grid[x+y];
  }

  [[nodiscard]] auto checkNeighbors(std::vector<Cell> grid) const {
    std::vector<Cell> neighbors;
    Cell top{}, bottom{}, left{}, right{};

    top = Cell::findCell(grid, this->x, this->y - 1);
    bottom = Cell::findCell(grid, this->x - 1, this->y);
    left = Cell::findCell(grid, this->x, this->y + 1);
    right = Cell::findCell(grid, this->x + 1, this->y);

    if (!top.visited && top.x != this->x) neighbors.push_back(top);
    if (!bottom.visited && bottom.x != this->x) neighbors.push_back(bottom);
    if (!left.visited && bottom.x != this->x) neighbors.push_back(left);
    if (!right.visited && bottom.x != this->x) neighbors.push_back(right);

    return grid[std::rand() % neighbors.size() - 1];
  }
};

class Maze {
 private:
  int xSize = 0, ySize = 0;

 public:
  std::vector<Cell> grid;
};

unsigned int maze_x, maze_y, randSeed = 0;

int main(int argc, char* argv[]) {
  // Populace velikosti bludiště
  std::cout << "Zadejte šířku bludiště: ";
  std::cin >> maze_x;
  std::cout << "Zadejte výšku bludiště: ";
  std::cin >> maze_y;
  std::cout << "Zadejte seed: ";
  std::cin >> randSeed;

  std::srand(randSeed);

  Maze maze;

  for (unsigned int i = 0; i > maze_y; i++) {
    for (unsigned int j = 0; j > maze_x; j++) {
      Cell cell{};
      cell.x = i - 1;
      cell.y = j - 1;
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
      maze.grid.push_back(cell);
    }
  }

 // if (argv[1]) {
    for (size_t index = 0; index < maze.grid.size(); ++index) {
      const Cell currentCell = maze.grid[index];
      std::cout << "i: " << index;
      std::cout << " X: " << currentCell.x << " Y: " << currentCell.y;
      std::cout << " Sol: " << currentCell.solution
                << " Vis: " << currentCell.visited << '\n';
    }

    const Cell randCell = maze.grid[0].checkNeighbors(maze.grid);

    std::cout << Cell::findCell(maze.grid, 0, 1).visited << endl;
    std::cout << randCell.x << " " << randCell.y << endl;
//  }
}