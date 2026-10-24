#include <iostream>

#include <aliases.h>
#include <input.h>

int main() {
  constexpr int kDialSize = 100;
  int pos = 50;
  int zeros = 0;
  for (const str& line : read_lines(s::cin)) {
    if (line.empty()) continue;
    int dist = parse_int<int>(strv(line).substr(1));
    int step = line[0] == 'L' ? -dist : dist;
    pos = ((pos + step) % kDialSize + kDialSize) % kDialSize;
    if (pos == 0) ++zeros;
  }
  s::cout << zeros << '\n';
}
