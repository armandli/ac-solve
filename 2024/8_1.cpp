#include <iostream>

#include <aliases.h>
#include <day8.h>
#include <grid.h>

int main() {
  // One antinode beyond each antenna of a pair, twice as far from the other.
  s::cout << count_antinodes(read_grid(s::cin), 1, 1) << '\n';
}
