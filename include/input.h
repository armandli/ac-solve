#ifndef INPUT_H
#define INPUT_H

#include <cassert>

#include <charconv>
#include <istream>
#include <string>
#include <string_view>
#include <system_error>
#include <vector>

#include <aliases.h>

inline vec<str> read_lines(s::istream& in) {
  vec<str> lines;
  str line;
  while (s::getline(in, line)) {
    lines.push_back(line);
  }
  return lines;
}

// Assumes `text` is entirely a base-10 integer; asserts otherwise.
template<typename T = long long>
T parse_int(strv text) {
  T value{};
  [[maybe_unused]] auto [end, ec] = s::from_chars(text.data(), text.data() + text.size(), value);
  assert(ec == s::errc() and end == text.data() + text.size());
  return value;
}

#endif  // INPUT_H
