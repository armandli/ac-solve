#ifndef DAY14_H
#define DAY14_H

#include <istream>
#include <vector>

#include <aliases.h>
#include <input.h>

inline constexpr int kSpaceWidth = 101;
inline constexpr int kSpaceHeight = 103;

struct Robot {
  int px, py;
  int vx, vy;
};

// "p=x,y v=x,y" per line.
inline vec<Robot> read_robots(s::istream& in) {
  vec<Robot> robots;
  for (const str& line : read_lines(in)) {
    vec<int> n = extract_signed_numbers<int>(line);
    if (n.size() == 4) robots.push_back({n[0], n[1], n[2], n[3]});
  }
  return robots;
}

// Coordinate after `seconds` along an axis of length `size` that wraps around.
inline int wrap_position(int position, int velocity, long long seconds, int size) {
  long long at = (position + velocity * (seconds % size)) % size;
  return static_cast<int>(at < 0 ? at + size : at);
}

#endif  // DAY14_H
