#include <algorithm>
#include <iostream>

#include <aliases.h>
#include <day10.h>
#include <grid.h>

int main() {
  Grid grid = read_grid(s::cin);
  long long total = 0;
  for (int row = 0; row < static_cast<int>(grid.size()); ++row) {
    for (int col = 0; col < static_cast<int>(grid[row].size()); ++col) {
      if (grid[row][col] != '0') continue;
      vec<Cell> summits;
      climb(grid, {row, col}, [&](Cell summit) {
        if (sr::find(summits, summit) == summits.end()) summits.push_back(summit);
      });
      total += summits.size();
    }
  }
  s::cout << total << '\n';
}
