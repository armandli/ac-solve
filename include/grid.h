#ifndef GRID_H
#define GRID_H

#include <array>
#include <istream>
#include <optional>
#include <string>
#include <string_view>
#include <vector>

#include <aliases.h>
#include <input.h>

// A rectangular character grid indexed as grid[row][col].
using Grid = vec<str>;

struct Offset {
  int dr;
  int dc;
};

// Up, right, down, left: stepping to the next entry is a 90 degree right turn.
inline constexpr s::array<Offset, 4> kNeighbors4 = {{{-1, 0}, {0, 1}, {1, 0}, {0, -1}}};

// Index into kNeighbors4 of a '^', '>', 'v' or '<' arrow.
inline size_t heading_of(char arrow) {
  return strv("^>v<").find(arrow);
}

inline constexpr s::array<Offset, 8> kNeighbors8 = {{
  {-1, -1}, {-1, 0}, {-1, 1},
  {0, -1},           {0, 1},
  {1, -1},  {1, 0},  {1, 1},
}};

// Reads lines until EOF, dropping empty ones.
inline Grid read_grid(s::istream& in) {
  Grid grid;
  for (str& line : read_lines(in)) {
    if (not line.empty()) grid.push_back(s::move(line));
  }
  return grid;
}

inline bool in_bounds(const Grid& grid, int row, int col) {
  return row >= 0 and row < static_cast<int>(grid.size()) and col >= 0 and
         col < static_cast<int>(grid[row].size());
}

struct Cell {
  int row;
  int col;

  bool operator==(const Cell&) const = default;
};

// First cell holding `ch` in reading order.
inline opt<Cell> find_cell(const Grid& grid, char ch) {
  for (int row = 0; row < static_cast<int>(grid.size()); ++row) {
    size_t col = grid[row].find(ch);
    if (col != str::npos) return Cell{row, static_cast<int>(col)};
  }
  return s::nullopt;
}

// Number of the eight surrounding cells holding `ch`.
inline int count_neighbors(const Grid& grid, int row, int col, char ch) {
  int count = 0;
  for (auto [dr, dc] : kNeighbors8) {
    if (in_bounds(grid, row + dr, col + dc) and grid[row + dr][col + dc] == ch) ++count;
  }
  return count;
}

inline constexpr int kUnreached = -1;

// Fewest orthogonal steps from `start` to each cell without entering `wall`,
// as distances[row][col]; kUnreached where there is no way through.
inline vec<vec<int>> bfs_distances(const Grid& grid, Cell start, char wall = '#') {
  vec<vec<int>> distances(grid.size(), vec<int>(grid[0].size(), kUnreached));
  vec<Cell> queue{start};
  distances[start.row][start.col] = 0;
  for (size_t head = 0; head < queue.size(); ++head) {
    Cell at = queue[head];
    for (auto [dr, dc] : kNeighbors4) {
      Cell next{at.row + dr, at.col + dc};
      if (not in_bounds(grid, next.row, next.col) or grid[next.row][next.col] == wall or
          distances[next.row][next.col] != kUnreached) {
        continue;
      }
      distances[next.row][next.col] = distances[at.row][at.col] + 1;
      queue.push_back(next);
    }
  }
  return distances;
}

#endif  // GRID_H
