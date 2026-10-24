#ifndef DAY7_H
#define DAY7_H

#include <cstdint>

#include <vector>

#include <aliases.h>
#include <grid.h>

struct BeamStats {
  long long splits;     // splitters hit by at least one beam
  uint64_t timelines;   // paths a single particle can take to the bottom
};

// Sweeps down row by row tracking how many timelines sit in each column;
// merged classical beams are just columns with a non-zero count.
inline BeamStats trace_beams(const Grid& grid) {
  BeamStats stats{0, 0};
  vec<uint64_t> paths(grid[0].size(), 0);
  paths[grid[0].find('S')] = 1;
  for (size_t row = 1; row < grid.size(); ++row) {
    vec<uint64_t> next(paths.size(), 0);
    for (size_t col = 0; col < paths.size(); ++col) {
      if (paths[col] == 0) continue;
      if (grid[row][col] != '^') {
        next[col] += paths[col];
        continue;
      }
      ++stats.splits;
      if (col > 0) next[col - 1] += paths[col];
      if (col + 1 < paths.size()) next[col + 1] += paths[col];
    }
    paths = s::move(next);
  }
  for (uint64_t count : paths) stats.timelines += count;
  return stats;
}

#endif  // DAY7_H
