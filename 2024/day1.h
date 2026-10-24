#ifndef DAY1_H
#define DAY1_H

#include <istream>
#include <string>
#include <vector>

#include <aliases.h>
#include <input.h>

struct Lists {
  vec<long long> left;
  vec<long long> right;
};

// One "left   right" pair of location IDs per line.
inline Lists read_lists(s::istream& in) {
  Lists lists;
  for (const str& line : read_lines(in)) {
    vec<long long> pair = extract_numbers(line);
    if (pair.size() != 2) continue;
    lists.left.push_back(pair[0]);
    lists.right.push_back(pair[1]);
  }
  return lists;
}

#endif  // DAY1_H
