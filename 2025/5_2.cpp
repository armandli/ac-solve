#include <iostream>

#include <aliases.h>
#include <day5.h>

int main() {
  long long total = 0;
  for (const Interval& range : read_database(s::cin).fresh) total += range.size();
  s::cout << total << '\n';
}
