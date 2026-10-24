#ifndef DAY4_H
#define DAY4_H

#include <aliases.h>
#include <grid.h>

inline constexpr char kRoll = '@';

// A forklift can reach a roll with fewer than four rolls around it.
inline bool accessible(const Grid& grid, int row, int col) {
  return grid[row][col] == kRoll and count_neighbors(grid, row, col, kRoll) < 4;
}

#endif  // DAY4_H
