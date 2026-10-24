#include <iostream>

#include <aliases.h>
#include <day16.h>
#include <grid.h>

int main() {
  Grid grid = read_grid(s::cin);
  s::cout << best_score(maze_scores(grid, maze_start(grid), false), maze_end(grid)) << '\n';
}
