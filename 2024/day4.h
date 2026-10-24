#ifndef DAY4_H
#define DAY4_H

#include <aliases.h>
#include <grid.h>

// Whether `word` is spelled starting at (row, col) and stepping by `dir`.
inline bool spells(const Grid& grid, int row, int col, Offset dir, strv word) {
  for (size_t i = 0; i < word.size(); ++i) {
    int r = row + dir.dr * static_cast<int>(i);
    int c = col + dir.dc * static_cast<int>(i);
    if (not in_bounds(grid, r, c) or grid[r][c] != word[i]) return false;
  }
  return true;
}

#endif  // DAY4_H
