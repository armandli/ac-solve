#ifndef DAY20_H
#define DAY20_H

#include <cstdlib>

#include <vector>

#include <aliases.h>
#include <grid.h>

// Cheats lasting at most `max_cheat` picoseconds that save at least
// `min_saving`. A cheat from track cell p to track cell q, a Manhattan
// distance d apart, finishes in from_start[p] + d + to_end[q].
inline long long count_cheats(const Grid& grid, int max_cheat, int min_saving) {
  Cell start = *find_cell(grid, 'S');
  vec<vec<int>> from_start = bfs_distances(grid, start);
  vec<vec<int>> to_end = bfs_distances(grid, *find_cell(grid, 'E'));
  int fastest = to_end[start.row][start.col];
  long long count = 0;
  for (int row = 0; row < static_cast<int>(grid.size()); ++row) {
    for (int col = 0; col < static_cast<int>(grid[row].size()); ++col) {
      if (from_start[row][col] == kUnreached) continue;
      for (int dr = -max_cheat; dr <= max_cheat; ++dr) {
        int reach = max_cheat - s::abs(dr);
        for (int dc = -reach; dc <= reach; ++dc) {
          int r = row + dr;
          int c = col + dc;
          if (not in_bounds(grid, r, c) or to_end[r][c] == kUnreached) continue;
          int time = from_start[row][col] + s::abs(dr) + s::abs(dc) + to_end[r][c];
          if (fastest - time >= min_saving) ++count;
        }
      }
    }
  }
  return count;
}

#endif  // DAY20_H
