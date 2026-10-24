#ifndef DAY5_H
#define DAY5_H

#include <algorithm>
#include <istream>
#include <set>
#include <string>
#include <utility>
#include <vector>

#include <aliases.h>
#include <input.h>

struct PrintQueue {
  s::set<s::pair<int, int>> rules;  // (x, y): x must print before y
  vec<vec<int>> updates;
};

// "X|Y" rules, a blank line, then comma-separated updates.
inline PrintQueue read_print_queue(s::istream& in) {
  PrintQueue queue;
  for (const str& line : read_lines(in)) {
    vec<int> numbers = extract_numbers<int>(line);
    if (numbers.empty()) continue;
    if (line.find('|') != str::npos) {
      queue.rules.insert({numbers[0], numbers[1]});
    } else {
      queue.updates.push_back(s::move(numbers));
    }
  }
  return queue;
}

// Orders pages by the rules. The puzzle gives a rule for every pair of pages
// that share an update, so this is a total order within each update.
struct PageOrder {
  const PrintQueue& queue;
  bool operator()(int a, int b) const { return queue.rules.contains({a, b}); }
};

#endif  // DAY5_H
