#ifndef DAY5_H
#define DAY5_H

#include <istream>
#include <string>
#include <vector>

#include <aliases.h>
#include <input.h>
#include <interval.h>

struct Database {
  vec<Interval> fresh;  // merged
  vec<long long> available;
};

// Fresh ranges, a blank line, then one available ingredient ID per line.
inline Database read_database(s::istream& in) {
  Database db;
  vec<Interval> ranges;
  bool in_ranges = true;
  for (const str& line : read_lines(in)) {
    strv text = trim(line);
    if (text.empty()) {
      in_ranges = false;
    } else if (in_ranges) {
      ranges.push_back(parse_interval(text));
    } else {
      db.available.push_back(parse_int(text));
    }
  }
  db.fresh = merge_intervals(s::move(ranges));
  return db;
}

#endif  // DAY5_H
