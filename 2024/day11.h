#ifndef DAY11_H
#define DAY11_H

#include <istream>
#include <unordered_map>
#include <vector>

#include <aliases.h>
#include <input.h>

inline vec<long long> read_stones(s::istream& in) {
  return extract_numbers(read_all(in));
}

// Stones in the line after `blinks` blinks. Order never affects how a stone
// evolves, so only the count of stones per engraving is tracked.
inline long long count_stones(const vec<long long>& stones, int blinks) {
  umap<long long, long long> counts;
  for (long long stone : stones) ++counts[stone];
  for (int blink = 0; blink < blinks; ++blink) {
    umap<long long, long long> next;
    for (auto [stone, count] : counts) {
      if (stone == 0) {
        next[1] += count;
        continue;
      }
      int digits = 0;
      long long half = 1;  // 10 to the power of half the digits
      for (long long rest = stone; rest > 0; rest /= 10) {
        if (++digits % 2 == 0) half *= 10;
      }
      if (digits % 2 == 0) {
        next[stone / half] += count;
        next[stone % half] += count;
      } else {
        next[stone * 2024] += count;
      }
    }
    counts = s::move(next);
  }
  long long total = 0;
  for (auto [stone, count] : counts) total += count;
  return total;
}

#endif  // DAY11_H
