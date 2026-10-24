#include <iostream>

#include <aliases.h>
#include <day2.h>

int main() {
  s::cout << sum_invalid_ids(s::cin, [](strv digits) {
    for (size_t block = 1; block <= digits.size() / 2; ++block) {
      if (is_repetition(digits, block)) return true;
    }
    return false;
  }) << '\n';
}
