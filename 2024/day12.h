#ifndef DAY12_H
#define DAY12_H

#include <vector>

#include <aliases.h>
#include <grid.h>

struct Region {
  long long area = 0;
  long long perimeter = 0;
  long long sides = 0;
};

// Every maximal group of orthogonally connected plots growing the same plant.
inline vec<Region> find_regions(const Grid& grid) {
  auto same = [&](Cell cell, int dr, int dc) {
    int row = cell.row + dr;
    int col = cell.col + dc;
    return in_bounds(grid, row, col) and grid[row][col] == grid[cell.row][cell.col];
  };
  vec<Region> regions;
  vec<vec<bool>> seen(grid.size(), vec<bool>(grid[0].size(), false));
  for (int row = 0; row < static_cast<int>(grid.size()); ++row) {
    for (int col = 0; col < static_cast<int>(grid[row].size()); ++col) {
      if (seen[row][col]) continue;
      Region region;
      vec<Cell> stack{{row, col}};
      seen[row][col] = true;
      while (not stack.empty()) {
        Cell at = stack.back();
        stack.pop_back();
        ++region.area;
        for (size_t heading = 0; heading < kNeighbors4.size(); ++heading) {
          Offset dir = kNeighbors4[heading];
          if (not same(at, dir.dr, dir.dc)) {
            ++region.perimeter;
          } else if (not seen[at.row + dir.dr][at.col + dir.dc]) {
            seen[at.row + dir.dr][at.col + dir.dc] = true;
            stack.push_back({at.row + dir.dr, at.col + dir.dc});
          }
          // A region has as many sides as corners. Check the corner between
          // this heading and the next one clockwise: it is convex when both
          // neighbours differ, concave when both match but the diagonal does not.
          Offset turn = kNeighbors4[(heading + 1) % kNeighbors4.size()];
          bool ahead = same(at, dir.dr, dir.dc);
          bool beside = same(at, turn.dr, turn.dc);
          bool diagonal = same(at, dir.dr + turn.dr, dir.dc + turn.dc);
          if ((not ahead and not beside) or (ahead and beside and not diagonal)) ++region.sides;
        }
      }
      regions.push_back(region);
    }
  }
  return regions;
}

#endif  // DAY12_H
