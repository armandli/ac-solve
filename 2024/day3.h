#ifndef DAY3_H
#define DAY3_H

#include <cctype>

#include <string>

#include <aliases.h>
#include <input.h>

// Consumes a run of 1-3 digits from the front of `text`.
inline opt<long long> take_operand(strv& text) {
  size_t len = 0;
  while (len < text.size() and len < 3 and s::isdigit(static_cast<unsigned char>(text[len]))) ++len;
  if (len == 0) return s::nullopt;
  long long value = parse_int(text.substr(0, len));
  text.remove_prefix(len);
  return value;
}

// Product of a well-formed "mul(X,Y)" at the start of `text`.
inline opt<long long> parse_mul(strv text) {
  if (not text.starts_with("mul(")) return s::nullopt;
  text.remove_prefix(4);
  opt<long long> x = take_operand(text);
  if (not x or not text.starts_with(',')) return s::nullopt;
  text.remove_prefix(1);
  opt<long long> y = take_operand(text);
  if (not y or not text.starts_with(')')) return s::nullopt;
  return *x * *y;
}

// Sum of every mul in `memory`; with `conditionals`, don't() and do()
// switch the following muls off and back on.
inline long long run_memory(strv memory, bool conditionals) {
  long long total = 0;
  bool enabled = true;
  for (size_t i = 0; i < memory.size(); ++i) {
    strv rest = memory.substr(i);
    if (conditionals and rest.starts_with("do()")) {
      enabled = true;
    } else if (conditionals and rest.starts_with("don't()")) {
      enabled = false;
    } else if (enabled) {
      if (opt<long long> product = parse_mul(rest)) total += *product;
    }
  }
  return total;
}

#endif  // DAY3_H
