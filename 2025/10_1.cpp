#include <algorithm>
#include <climits>
#include <iostream>

#include <aliases.h>
#include <day10.h>

int main() {
  long long total = 0;
  for (const Machine& machine : read_machines(s::cin)) {
    int fewest = INT_MAX;
    for (const Combo& combo : single_press_combos(machine)) {
      if (combo.parity == machine.lights) fewest = s::min(fewest, combo.presses);
    }
    total += fewest;
  }
  s::cout << total << '\n';
}
