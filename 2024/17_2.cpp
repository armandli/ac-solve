#include <algorithm>
#include <iostream>
#include <vector>

#include <aliases.h>
#include <day17.h>

int main() {
  Computer computer = read_computer(s::cin);
  const vec<int>& program = computer.program;
  // The program loops shifting A right by 3 bits and printing one digit each
  // round, so the final digits depend only on A's highest bits. Build A three
  // bits at a time, keeping every prefix whose output matches the program's
  // tail.
  vec<long long> candidates{0};
  for (size_t matched = 1; matched <= program.size(); ++matched) {
    vec<int> tail(program.end() - matched, program.end());
    vec<long long> next;
    for (long long prefix : candidates) {
      for (long long bits = 0; bits < 8; ++bits) {
        long long a = prefix * 8 + bits;
        if (a > 0 and run(program, a, computer.b, computer.c) == tail) next.push_back(a);
      }
    }
    candidates = s::move(next);
  }
  if (candidates.empty()) {
    s::cout << "no value of A makes the program print itself\n";
    return 0;
  }
  s::cout << *sr::min_element(candidates) << '\n';
}
