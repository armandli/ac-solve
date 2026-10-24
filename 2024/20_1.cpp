#include <iostream>

#include <aliases.h>
#include <day20.h>
#include <grid.h>

int main() {
  s::cout << count_cheats(read_grid(s::cin), 2, 100) << '\n';
}
