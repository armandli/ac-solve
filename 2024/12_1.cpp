#include <iostream>

#include <aliases.h>
#include <day12.h>
#include <grid.h>

int main() {
  long long total = 0;
  for (const Region& region : find_regions(read_grid(s::cin))) {
    total += region.area * region.perimeter;
  }
  s::cout << total << '\n';
}
