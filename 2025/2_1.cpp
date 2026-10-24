#include <iostream>

#include <aliases.h>
#include <day2.h>

int main() {
  s::cout << sum_invalid_ids(s::cin, [](strv digits) {
    return digits.size() % 2 == 0 and is_repetition(digits, digits.size() / 2);
  }) << '\n';
}
