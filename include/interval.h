#ifndef INTERVAL_H
#define INTERVAL_H

#include <algorithm>
#include <vector>

#include <aliases.h>
#include <input.h>

// Closed integer interval [lo, hi].
struct Interval {
  long long lo;
  long long hi;

  long long size() const { return hi - lo + 1; }
  bool contains(long long value) const { return lo <= value and value <= hi; }
};

// Parses "lo-hi".
inline Interval parse_interval(strv text) {
  size_t dash = text.find('-');
  return {parse_int(trim(text.substr(0, dash))), parse_int(trim(text.substr(dash + 1)))};
}

// Sorted, disjoint, non-adjacent intervals covering the same values.
inline vec<Interval> merge_intervals(vec<Interval> intervals) {
  sr::sort(intervals, {}, &Interval::lo);
  vec<Interval> merged;
  for (const Interval& interval : intervals) {
    if (not merged.empty() and interval.lo <= merged.back().hi + 1) {
      merged.back().hi = s::max(merged.back().hi, interval.hi);
    } else {
      merged.push_back(interval);
    }
  }
  return merged;
}

#endif  // INTERVAL_H
