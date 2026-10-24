#ifndef DAY9_H
#define DAY9_H

#include <cstdlib>

#include <istream>
#include <string>
#include <vector>

#include <aliases.h>
#include <input.h>

struct Tile {
  long long x;
  long long y;
};

inline vec<Tile> read_tiles(s::istream& in) {
  vec<Tile> tiles;
  for (const str& line : read_lines(in)) {
    vec<long long> xy = extract_numbers(line);
    if (xy.size() == 2) tiles.push_back({xy[0], xy[1]});
  }
  return tiles;
}

// Tiles covered by the rectangle with opposite corners a and b, inclusive.
inline long long rect_area(Tile a, Tile b) {
  return (s::llabs(a.x - b.x) + 1) * (s::llabs(a.y - b.y) + 1);
}

#endif  // DAY9_H
