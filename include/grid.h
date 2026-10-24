#ifndef GRID_H
#define GRID_H

#include <array>
#include <istream>
#include <optional>
#include <string>
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

#endif  // GRID_H
