#include <iostream>
#include <vector>

#include <aliases.h>
#include <day6.h>

int main() {
  long long total = 0;
  for (const Problem& problem : read_worksheet(s::cin)) {
    // Each column is one number, most significant digit on top. Column order
    // does not matter since both operators are commutative.
    vec<long long> numbers;
    for (size_t col = 0; col < problem.rows[0].size(); ++col) {
      long long number = 0;
      for (const str& row : problem.rows) {
        if (row[col] != ' ') number = number * 10 + (row[col] - '0');
      }
      numbers.push_back(number);
    }
    total += evaluate(problem.op, numbers);
  }
  s::cout << total << '\n';
}
