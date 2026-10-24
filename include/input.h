#ifndef INPUT_H
#define INPUT_H

#include <cassert>
#include <cctype>

#include <charconv>
#include <istream>
#include <iterator>
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

// The whole stream, newlines included.
inline str read_all(s::istream& in) {
  return str(s::istreambuf_iterator<char>(in), {});
}

// Assumes `text` is entirely a base-10 integer; asserts otherwise.
template<typename T = long long>
T parse_int(strv text) {
  T value{};
  [[maybe_unused]] auto [end, ec] = s::from_chars(text.data(), text.data() + text.size(), value);
  assert(ec == s::errc() and end == text.data() + text.size());
  return value;
}

// Splits on every `delim`; adjacent delimiters yield empty pieces.
inline vec<strv> split(strv text, char delim) {
  vec<strv> pieces;
  while (true) {
    size_t at = text.find(delim);
    pieces.push_back(text.substr(0, at));
    if (at == strv::npos) break;
    text.remove_prefix(at + 1);
  }
  return pieces;
}

inline strv trim(strv text) {
  size_t first = text.find_first_not_of(" \t\r");
  if (first == strv::npos) return {};
  size_t last = text.find_last_not_of(" \t\r");
  return text.substr(first, last - first + 1);
}

// Every run of decimal digits in `text`, in order, negated when `signed_runs`
// and directly preceded by '-'.
template<typename T>
vec<T> scan_numbers(strv text, bool signed_runs) {
  vec<T> numbers;
  size_t i = 0;
  while (i < text.size()) {
    if (not s::isdigit(static_cast<unsigned char>(text[i]))) {
      ++i;
      continue;
    }
    size_t j = i;
    while (j < text.size() and s::isdigit(static_cast<unsigned char>(text[j]))) ++j;
    T value = parse_int<T>(text.substr(i, j - i));
    numbers.push_back(signed_runs and i > 0 and text[i - 1] == '-' ? -value : value);
    i = j;
  }
  return numbers;
}

// Every run of decimal digits in `text`, in order. Signs are not recognized.
template<typename T = long long>
vec<T> extract_numbers(strv text) {
  return scan_numbers<T>(text, false);
}

// Like extract_numbers, but a '-' directly before the digits negates them.
template<typename T = long long>
vec<T> extract_signed_numbers(strv text) {
  return scan_numbers<T>(text, true);
}

#endif  // INPUT_H
