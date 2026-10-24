#include <iostream>

#include <aliases.h>
#include <day19.h>

int main() {
  Onsen onsen = read_onsen(s::cin);
  long long possible = 0;
  for (const str& design : onsen.designs) {
    if (arrangements(design, onsen.towels) > 0) ++possible;
  }
  s::cout << possible << '\n';
}
