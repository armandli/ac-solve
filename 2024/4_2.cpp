#include <iostream>

#include <aliases.h>
#include <day4.h>
#include <grid.h>

// Both diagonals through (row, col) read MAS in either direction.
bool x_mas(const Grid& grid, int row, int col) {
  auto diagonal = [&](Offset dir) {
    return spells(grid, row - dir.dr, col - dir.dc, dir, "MAS") or
           spells(grid, row + dir.dr, col + dir.dc, {-dir.dr, -dir.dc}, "MAS");
  };
  return grid[row][col] == 'A' and diagonal({1, 1}) and diagonal({1, -1});
}

int main() {
  Grid grid = read_grid(s::cin);
  int count = 0;
  for (int row = 0; row < static_cast<int>(grid.size()); ++row) {
    for (int col = 0; col < static_cast<int>(grid[row].size()); ++col) {
      if (x_mas(grid, row, col)) ++count;
    }
  }
  s::cout << count << '\n';
}
