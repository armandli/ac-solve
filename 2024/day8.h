#ifndef DAY8_H
#define DAY8_H

#include <map>
#include <vector>

#include <aliases.h>
#include <grid.h>

// Distinct in-bounds cells a + k * (a - b) for some pair of same-frequency
// antennas a, b and some k in [min_k, max_k].
inline size_t count_antinodes(const Grid& grid, int min_k, int max_k) {
  s::map<char, vec<Cell>> antennas;
  for (int row = 0; row < static_cast<int>(grid.size()); ++row) {
    for (int col = 0; col < static_cast<int>(grid[row].size()); ++col) {
      if (grid[row][col] != '.') antennas[grid[row][col]].push_back({row, col});
    }
  }
  vec<str> marked(grid.size(), str(grid[0].size(), '.'));
  size_t count = 0;
  for (const auto& [frequency, cells] : antennas) {
    for (const Cell& a : cells) {
      for (const Cell& b : cells) {
        if (a == b) continue;
        Offset step{a.row - b.row, a.col - b.col};
        for (int k = min_k; k <= max_k; ++k) {
          int row = a.row + k * step.dr;
          int col = a.col + k * step.dc;
          if (not in_bounds(grid, row, col)) break;
          if (marked[row][col] == '#') continue;
          marked[row][col] = '#';
          ++count;
        }
      }
    }
  }
  return count;
}

#endif  // DAY8_H
