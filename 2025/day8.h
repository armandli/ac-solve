#ifndef DAY8_H
#define DAY8_H

#include <algorithm>
#include <istream>
#include <string>
#include <vector>

#include <aliases.h>
#include <input.h>

struct Box {
  long long x;
  long long y;
  long long z;
};

// A candidate string of lights between boxes a and b.
struct Link {
  long long dist2;  // squared straight-line distance
  size_t a;
  size_t b;
};

inline vec<Box> read_boxes(s::istream& in) {
  vec<Box> boxes;
  for (const str& line : read_lines(in)) {
    vec<long long> xyz = extract_numbers(line);
    if (xyz.size() == 3) boxes.push_back({xyz[0], xyz[1], xyz[2]});
  }
  return boxes;
}

// Every pair of boxes, closest first.
inline vec<Link> links_by_distance(const vec<Box>& boxes) {
  vec<Link> links;
  links.reserve(boxes.size() * (boxes.size() - 1) / 2);
  for (size_t a = 0; a < boxes.size(); ++a) {
    for (size_t b = a + 1; b < boxes.size(); ++b) {
      long long dx = boxes[a].x - boxes[b].x;
      long long dy = boxes[a].y - boxes[b].y;
      long long dz = boxes[a].z - boxes[b].z;
      links.push_back({dx * dx + dy * dy + dz * dz, a, b});
    }
  }
  sr::sort(links, {}, &Link::dist2);
  return links;
}

#endif  // DAY8_H
