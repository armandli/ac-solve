#ifndef DAY3_H
#define DAY3_H

#include <istream>
#include <string>

#include <aliases.h>
#include <input.h>

// Largest number formed by keeping `count` digits of `bank` in order. Each
// digit greedily takes the biggest value that still leaves room for the rest.
inline long long max_joltage(strv bank, size_t count) {
  long long joltage = 0;
  size_t start = 0;
  for (size_t left = count; left > 0; --left) {
    size_t best = start;
    for (size_t i = start; i + left <= bank.size(); ++i) {
      if (bank[i] > bank[best]) best = i;
    }
    joltage = joltage * 10 + (bank[best] - '0');
    start = best + 1;
  }
  return joltage;
}

inline long long total_joltage(s::istream& in, size_t count) {
  long long total = 0;
  for (const str& line : read_lines(in)) {
    strv bank = trim(line);
    if (not bank.empty()) total += max_joltage(bank, count);
  }
  return total;
}

#endif  // DAY3_H
