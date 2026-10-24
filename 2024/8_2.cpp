#include <iostream>
#include <limits>

#include <aliases.h>
#include <day8.h>
#include <grid.h>

int main() {
  // Every multiple of the spacing along the line, antennas included.
  s::cout << count_antinodes(read_grid(s::cin), 0, s::numeric_limits<int>::max()) << '\n';
}
