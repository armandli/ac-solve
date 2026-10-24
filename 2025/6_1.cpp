#include <iostream>
#include <vector>

#include <aliases.h>
#include <day6.h>
#include <input.h>

int main() {
  long long total = 0;
  for (const Problem& problem : read_worksheet(s::cin)) {
    vec<long long> numbers;
    for (const str& row : problem.rows) numbers.push_back(parse_int(trim(row)));
    total += evaluate(problem.op, numbers);
  }
  s::cout << total << '\n';
}
