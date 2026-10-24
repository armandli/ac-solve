#include <iostream>

#include <aliases.h>
#include <day19.h>

int main() {
  Onsen onsen = read_onsen(s::cin);
  long long total = 0;
  for (const str& design : onsen.designs) total += arrangements(design, onsen.towels);
  s::cout << total << '\n';
}
