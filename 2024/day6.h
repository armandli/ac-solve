#ifndef DAY6_H
#define DAY6_H

#include <vector>

#include <aliases.h>
#include <grid.h>

inline constexpr char kObstacle = '#';

// Cells the guard covers before walking off the map, flagged at
// row * width + col; empty when she ends up circling forever.
inline opt<vec<bool>> patrol(const Grid& grid, Cell start) {
  int width = static_cast<int>(grid[0].size());
  vec<bool> visited(grid.size() * width, false);
  // A repeated (cell, heading) means the walk has entered a cycle.
  vec<bool> seen(visited.size() * kNeighbors4.size(), false);
  Cell at = start;
  size_t heading = 0;  // the guard starts facing up
  while (true) {
    size_t index = at.row * width + at.col;
    visited[index] = true;
    if (seen[index * kNeighbors4.size() + heading]) return s::nullopt;
    seen[index * kNeighbors4.size() + heading] = true;
    Offset dir = kNeighbors4[heading];
    Cell next{at.row + dir.dr, at.col + dir.dc};
    if (not in_bounds(grid, next.row, next.col)) return visited;
    if (grid[next.row][next.col] == kObstacle) {
      heading = (heading + 1) % kNeighbors4.size();
    } else {
      at = next;
    }
  }
}

#endif  // DAY6_H
