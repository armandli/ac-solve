#ifndef DAY18_H
#define DAY18_H

#include <istream>
#include <vector>

#include <aliases.h>
#include <grid.h>
#include <input.h>

inline constexpr int kMemorySize = 71;

// "X,Y" per line.
inline vec<Cell> read_falling_bytes(s::istream& in) {
  vec<Cell> bytes;
  for (const str& line : read_lines(in)) {
    vec<int> n = extract_numbers<int>(line);
    if (n.size() == 2) bytes.push_back({n[1], n[0]});
  }
  return bytes;
}

// The memory space with the first `count` bytes corrupted.
inline Grid corrupted_memory(const vec<Cell>& bytes, size_t count) {
  Grid grid(kMemorySize, str(kMemorySize, '.'));
  for (size_t i = 0; i < count; ++i) grid[bytes[i].row][bytes[i].col] = '#';
  return grid;
}

#endif  // DAY18_H
