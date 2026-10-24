#include <iostream>

#include <aliases.h>
#include <day4.h>
#include <grid.h>

int main() {
  Grid grid = read_grid(s::cin);
  int count = 0;
  for (int row = 0; row < static_cast<int>(grid.size()); ++row) {
    for (int col = 0; col < static_cast<int>(grid[row].size()); ++col) {
      for (Offset dir : kNeighbors8) {
        if (spells(grid, row, col, dir, "XMAS")) ++count;
      }
    }
  }
  s::cout << count << '\n';
}
