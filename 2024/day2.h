#ifndef DAY2_H
#define DAY2_H

#include <istream>
#include <string>
#include <vector>

#include <aliases.h>
#include <input.h>

inline vec<vec<int>> read_reports(s::istream& in) {
  vec<vec<int>> reports;
  for (const str& line : read_lines(in)) {
    vec<int> levels = extract_numbers<int>(line);
    if (not levels.empty()) reports.push_back(s::move(levels));
  }
  return reports;
}

// Strictly monotonic with every adjacent step between 1 and 3.
inline bool safe(const vec<int>& levels) {
  if (levels.size() < 2) return true;
  int sign = levels[1] > levels[0] ? 1 : -1;
  for (size_t i = 1; i < levels.size(); ++i) {
    int step = (levels[i] - levels[i - 1]) * sign;
    if (step < 1 or step > 3) return false;
  }
  return true;
}

#endif  // DAY2_H
