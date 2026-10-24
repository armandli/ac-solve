#include <iostream>

#include <aliases.h>
#include <input.h>

int main() {
  constexpr int kDialSize = 100;
  int pos = 50;
  long long zeros = 0;
  for (const str& line : read_lines(s::cin)) {
    if (line.empty()) continue;
    int dist = parse_int<int>(strv(line).substr(1));
    if (line[0] == 'R') {
      zeros += (pos + dist) / kDialSize;
      pos = (pos + dist) % kDialSize;
    } else {
      // Clicks until the first zero going left: pos, or a full turn from 0.
      int first = pos == 0 ? kDialSize : pos;
      if (dist >= first) zeros += (dist - first) / kDialSize + 1;
      pos = ((pos - dist) % kDialSize + kDialSize) % kDialSize;
    }
  }
  s::cout << zeros << '\n';
}
