#ifndef DAY7_H
#define DAY7_H

#include <istream>
#include <string>
#include <vector>

#include <aliases.h>
#include <input.h>

struct Equation {
  long long target;
  vec<long long> operands;
};

// "target: a b c ..."
inline vec<Equation> read_equations(s::istream& in) {
  vec<Equation> equations;
  for (const str& line : read_lines(in)) {
    vec<long long> numbers = extract_numbers(line);
    if (numbers.size() < 2) continue;
    equations.push_back({numbers[0], vec<long long>(numbers.begin() + 1, numbers.end())});
  }
  return equations;
}

// Whether operands[0..count) can reach `target` evaluating left to right.
// Works backwards from the last operand, undoing each candidate operator, so
// impossible branches are cut as soon as a subtraction, division or digit
// strip fails.
inline bool reachable(long long target, const vec<long long>& operands, size_t count,
                      bool concatenation) {
  long long last = operands[count - 1];
  if (count == 1) return target == last;
  if (target >= last and reachable(target - last, operands, count - 1, concatenation)) {
    return true;
  }
  if (last != 0 and target % last == 0 and
      reachable(target / last, operands, count - 1, concatenation)) {
    return true;
  }
  if (concatenation) {
    long long power = 10;
    while (power <= last) power *= 10;
    if (target > last and target % power == last and
        reachable(target / power, operands, count - 1, concatenation)) {
      return true;
    }
  }
  return false;
}

inline long long calibration(const vec<Equation>& equations, bool concatenation) {
  long long total = 0;
  for (const Equation& eq : equations) {
    if (reachable(eq.target, eq.operands, eq.operands.size(), concatenation)) total += eq.target;
  }
  return total;
}

#endif  // DAY7_H
