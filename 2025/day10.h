#ifndef DAY10_H
#define DAY10_H

#include <bit>
#include <istream>
#include <string>
#include <vector>

#include <aliases.h>
#include <input.h>

struct Machine {
  unsigned lights;           // bit i set when light i must end up on
  vec<vec<int>> buttons;     // indices each button toggles or increments
  vec<long long> joltage;
};

// "[.##.] (3) (1,3) ... {3,5,4,7}"
inline Machine parse_machine(strv line) {
  Machine machine{0, {}, {}};
  for (strv token : split(line, ' ')) {
    if (token.empty()) continue;
    switch (token[0]) {
    case '[':
      for (size_t i = 1; i + 1 < token.size(); ++i) {
        if (token[i] == '#') machine.lights |= 1u << (i - 1);
      }

    break; case '(':
      machine.buttons.push_back(extract_numbers<int>(token));

    break; case '{':
      machine.joltage = extract_numbers(token);

    break; default:
      break;
    }
  }
  return machine;
}

inline vec<Machine> read_machines(s::istream& in) {
  vec<Machine> machines;
  for (const str& line : read_lines(in)) {
    if (not trim(line).empty()) machines.push_back(parse_machine(line));
  }
  return machines;
}

// The outcome of pressing a subset of the buttons once each.
struct Combo {
  int presses;
  unsigned parity;      // lights left on, i.e. counters left odd
  vec<long long> gain;  // amount added to each counter
};

// All 2^buttons combos. Pressing a button twice is a no-op for the lights,
// so every useful light configuration is one of these.
inline vec<Combo> single_press_combos(const Machine& machine) {
  size_t count = machine.buttons.size();
  size_t counters = s::max<size_t>(machine.joltage.size(), s::bit_width(machine.lights));
  vec<Combo> combos;
  combos.reserve(size_t{1} << count);
  for (unsigned subset = 0; subset < (1u << count); ++subset) {
    Combo combo{s::popcount(subset), 0, vec<long long>(counters, 0)};
    for (size_t b = 0; b < count; ++b) {
      if (not (subset >> b & 1)) continue;
      for (int index : machine.buttons[b]) {
        combo.parity ^= 1u << index;
        ++combo.gain[index];
      }
    }
    combos.push_back(s::move(combo));
  }
  return combos;
}

#endif  // DAY10_H
