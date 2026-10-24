#ifndef DAY13_H
#define DAY13_H

#include <istream>
#include <vector>

#include <aliases.h>
#include <input.h>

struct ClawMachine {
  long long ax, ay;  // claw movement per A press
  long long bx, by;  // claw movement per B press
  long long px, py;  // prize position
};

inline vec<ClawMachine> read_claw_machines(s::istream& in) {
  vec<long long> numbers = extract_numbers(read_all(in));
  vec<ClawMachine> machines;
  for (size_t i = 0; i + 6 <= numbers.size(); i += 6) {
    machines.push_back({numbers[i], numbers[i + 1], numbers[i + 2], numbers[i + 3],
                        numbers[i + 4], numbers[i + 5]});
  }
  return machines;
}

struct Presses {
  long long a;
  long long b;

  long long tokens() const { return 3 * a + b; }
};

// The presses landing the claw on the prize, if any. Each machine is a pair
// of linear equations; the puzzle's buttons are never parallel, so Cramer's
// rule gives the only candidate.
inline opt<Presses> win(const ClawMachine& m) {
  long long det = m.ax * m.by - m.ay * m.bx;
  long long a = m.px * m.by - m.py * m.bx;
  long long b = m.ax * m.py - m.ay * m.px;
  if (det == 0 or a % det != 0 or b % det != 0) return s::nullopt;
  a /= det;
  b /= det;
  if (a < 0 or b < 0) return s::nullopt;
  return Presses{a, b};
}

#endif  // DAY13_H
