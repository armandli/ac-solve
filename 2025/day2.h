#ifndef DAY2_H
#define DAY2_H

#include <istream>
#include <string>

#include <aliases.h>
#include <input.h>
#include <interval.h>

// True when `digits` is its first `block` characters repeated end to end.
inline bool is_repetition(strv digits, size_t block) {
  if (block == 0 or digits.size() % block != 0) return false;
  for (size_t i = block; i < digits.size(); ++i) {
    if (digits[i] != digits[i - block]) return false;
  }
  return true;
}

// Sums every ID in the comma-separated ranges for which `invalid(digits)` holds.
template<typename Pred>
long long sum_invalid_ids(s::istream& in, Pred invalid) {
  long long total = 0;
  for (const str& line : read_lines(in)) {
    for (strv piece : split(line, ',')) {
      if (trim(piece).empty()) continue;
      Interval range = parse_interval(piece);
      for (long long id = range.lo; id <= range.hi; ++id) {
        if (invalid(s::to_string(id))) total += id;
      }
    }
  }
  return total;
}

#endif  // DAY2_H
