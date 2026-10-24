#ifndef DAY19_H
#define DAY19_H

#include <istream>
#include <vector>

#include <aliases.h>
#include <input.h>

struct Onsen {
  vec<str> towels;
  vec<str> designs;
};

// Comma-separated towel patterns, a blank line, then one design per line.
inline Onsen read_onsen(s::istream& in) {
  Onsen onsen;
  vec<str> lines = read_lines(in);
  for (strv towel : split(lines[0], ',')) onsen.towels.emplace_back(trim(towel));
  for (size_t i = 1; i < lines.size(); ++i) {
    if (not trim(lines[i]).empty()) onsen.designs.emplace_back(trim(lines[i]));
  }
  return onsen;
}

// Number of towel sequences that spell out `design`.
inline long long arrangements(strv design, const vec<str>& towels) {
  // ways[i]: arrangements of the first i stripes.
  vec<long long> ways(design.size() + 1, 0);
  ways[0] = 1;
  for (size_t i = 0; i < design.size(); ++i) {
    if (ways[i] == 0) continue;
    for (const str& towel : towels) {
      if (design.substr(i).starts_with(towel)) ways[i + towel.size()] += ways[i];
    }
  }
  return ways.back();
}

#endif  // DAY19_H
