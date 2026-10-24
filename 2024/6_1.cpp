#include <algorithm>
#include <iostream>

#include <aliases.h>
#include <day6.h>
#include <grid.h>

int main() {
  Grid grid = read_grid(s::cin);
  vec<bool> visited = *patrol(grid, *find_cell(grid, '^'));
  s::cout << sr::count(visited, true) << '\n';
}
