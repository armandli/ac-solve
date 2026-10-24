#ifndef DAY10_H
#define DAY10_H

#include <aliases.h>
#include <grid.h>

// Calls `reach(cell)` with the summit at the end of every distinct hiking
// trail from (row, col): a run of orthogonal steps climbing by exactly one.
template<typename Reach>
void climb(const Grid& grid, Cell from, Reach&& reach) {
  char height = grid[from.row][from.col];
  if (height == '9') {
    reach(from);
    return;
  }
  for (auto [dr, dc] : kNeighbors4) {
    Cell next{from.row + dr, from.col + dc};
    if (in_bounds(grid, next.row, next.col) and grid[next.row][next.col] == height + 1) {
      climb(grid, next, reach);
    }
  }
}

#endif  // DAY10_H
