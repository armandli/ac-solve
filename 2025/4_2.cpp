#include <iostream>

#include <aliases.h>
#include <day4.h>
#include <grid.h>

int main() {
  constexpr char kEmpty = '.';
  Grid grid = read_grid(s::cin);
  int removed = 0;
  // Removal only ever makes rolls more accessible, so sweep until stable.
  for (bool changed = true; changed;) {
    changed = false;
    for (int row = 0; row < static_cast<int>(grid.size()); ++row) {
      for (int col = 0; col < static_cast<int>(grid[row].size()); ++col) {
        if (not accessible(grid, row, col)) continue;
        grid[row][col] = kEmpty;
        ++removed;
        changed = true;
      }
    }
  }
  s::cout << removed << '\n';
}
