#ifndef DAY15_H
#define DAY15_H

#include <algorithm>
#include <istream>
#include <utility>
#include <vector>

#include <aliases.h>
#include <grid.h>
#include <input.h>

struct Warehouse {
  Grid grid;
  str moves;
};

// The map, a blank line, then arrows that may span several lines.
inline Warehouse read_warehouse(s::istream& in) {
  Warehouse warehouse;
  bool in_moves = false;
  for (const str& line : read_lines(in)) {
    if (line.empty()) {
      in_moves = not warehouse.grid.empty();
    } else if (in_moves) {
      warehouse.moves += line;
    } else {
      warehouse.grid.push_back(line);
    }
  }
  return warehouse;
}

// Doubles every tile's width, turning boxes into "[]".
inline Grid widen(const Grid& grid) {
  Grid wide;
  for (const str& line : grid) {
    str& row = wide.emplace_back();
    for (char ch : line) {
      row += ch == 'O' ? "[]" : ch == '@' ? "@." : str(2, ch);
    }
  }
  return wide;
}

// Moves the robot one step towards `heading`, pushing whatever boxes are in
// the way unless any of them would hit a wall.
inline void push(Grid& grid, Cell& robot, size_t heading) {
  Offset dir = kNeighbors4[heading];
  vec<Cell> moving{robot};
  auto add = [&](Cell cell) {
    if (sr::find(moving, cell) == moving.end()) moving.push_back(cell);
  };
  for (size_t i = 0; i < moving.size(); ++i) {
    Cell next{moving[i].row + dir.dr, moving[i].col + dir.dc};
    char ch = grid[next.row][next.col];
    if (ch == '#') return;
    if (ch == '.') continue;
    add(next);
    // Both halves of a wide box move together.
    if (ch == '[') add({next.row, next.col + 1});
    if (ch == ']') add({next.row, next.col - 1});
  }
  vec<char> tiles;
  for (Cell cell : moving) {
    tiles.push_back(s::exchange(grid[cell.row][cell.col], '.'));
  }
  for (size_t i = 0; i < moving.size(); ++i) {
    grid[moving[i].row + dir.dr][moving[i].col + dir.dc] = tiles[i];
  }
  robot = {robot.row + dir.dr, robot.col + dir.dc};
}

// Sum of the boxes' GPS coordinates after the robot makes every move.
inline long long gps_after_moves(Grid grid, const str& moves) {
  Cell robot = *find_cell(grid, '@');
  for (char move : moves) push(grid, robot, heading_of(move));
  long long sum = 0;
  for (int row = 0; row < static_cast<int>(grid.size()); ++row) {
    for (int col = 0; col < static_cast<int>(grid[row].size()); ++col) {
      if (grid[row][col] == 'O' or grid[row][col] == '[') sum += 100 * row + col;
    }
  }
  return sum;
}

#endif  // DAY15_H
