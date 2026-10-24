#ifndef DAY9_H
#define DAY9_H

#include <cctype>

#include <istream>
#include <vector>

#include <aliases.h>
#include <input.h>

inline constexpr int kFree = -1;

// One entry per block: the file ID stored there, or kFree.
inline vec<int> read_blocks(s::istream& in) {
  vec<int> blocks;
  int index = 0;
  for (char ch : read_all(in)) {
    if (not s::isdigit(static_cast<unsigned char>(ch))) continue;
    int id = index % 2 == 0 ? index / 2 : kFree;
    blocks.insert(blocks.end(), ch - '0', id);
    ++index;
  }
  return blocks;
}

inline long long checksum(const vec<int>& blocks) {
  long long sum = 0;
  for (size_t pos = 0; pos < blocks.size(); ++pos) {
    if (blocks[pos] != kFree) sum += static_cast<long long>(pos) * blocks[pos];
  }
  return sum;
}

#endif  // DAY9_H
