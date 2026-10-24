#include <algorithm>
#include <iostream>
#include <map>
#include <vector>

#include <aliases.h>
#include <day10.h>

namespace {

constexpr long long kImpossible = 1LL << 50;

// Any solution presses each button some n = (n mod 2) + 2k times. The odd
// leftovers form a single-press combo whose parity matches the targets, and
// what remains is twice a smaller solution for (target - gain) / 2.
struct JoltageSolver {
  umap<unsigned, vec<const Combo*>> combos_by_parity;
  s::map<vec<long long>, long long> memo;

  explicit JoltageSolver(const vec<Combo>& combos) {
    for (const Combo& combo : combos) combos_by_parity[combo.parity].push_back(&combo);
  }

  long long fewest(const vec<long long>& target) {
    if (sr::all_of(target, [](long long t) { return t == 0; })) return 0;
    if (auto it = memo.find(target); it != memo.end()) return it->second;
    unsigned parity = 0;
    for (size_t i = 0; i < target.size(); ++i) {
      if (target[i] % 2 != 0) parity |= 1u << i;
    }
    long long best = kImpossible;
    vec<long long> half(target.size());
    for (const Combo* combo : combos_by_parity[parity]) {
      bool fits = true;
      for (size_t i = 0; i < target.size() and fits; ++i) {
        fits = combo->gain[i] <= target[i];
        half[i] = (target[i] - combo->gain[i]) / 2;
      }
      if (fits) best = s::min(best, combo->presses + 2 * fewest(half));
    }
    return memo[target] = s::min(best, kImpossible);
  }
};

}  // namespace

int main() {
  long long total = 0;
  for (const Machine& machine : read_machines(s::cin)) {
    vec<Combo> combos = single_press_combos(machine);
    total += JoltageSolver(combos).fewest(machine.joltage);
  }
  s::cout << total << '\n';
}
