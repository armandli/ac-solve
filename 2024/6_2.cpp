#include <iostream>

#include <aliases.h>
#include <day6.h>
#include <grid.h>

int main() {
  Grid grid = read_grid(s::cin);
  Cell start = *find_cell(grid, '^');
  int width = static_cast<int>(grid[0].size());
  // An obstruction off the original route never meets the guard.
  vec<bool> route = *patrol(grid, start);
  int loops = 0;
  for (size_t index = 0; index < route.size(); ++index) {
    Cell cell{static_cast<int>(index) / width, static_cast<int>(index) % width};
    if (not route[index] or cell == start) continue;
    char& spot = grid[cell.row][cell.col];
    spot = kObstacle;
    if (not patrol(grid, start)) ++loops;
    spot = '.';
  }
  s::cout << loops << '\n';
}
