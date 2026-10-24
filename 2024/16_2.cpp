#include <iostream>

#include <aliases.h>
#include <day16.h>
#include <grid.h>

int main() {
  Grid grid = read_grid(s::cin);
  vec<long long> from_start = maze_scores(grid, maze_start(grid), false);
  vec<long long> to_end = maze_scores(grid, maze_end(grid), true);
  long long best = best_score(from_start, maze_end(grid));
  // A state lies on a best path when the best route through it costs `best`.
  long long tiles = 0;
  for (size_t cell = 0; cell * kNeighbors4.size() < from_start.size(); ++cell) {
    for (size_t heading = 0; heading < kNeighbors4.size(); ++heading) {
      size_t state = cell * kNeighbors4.size() + heading;
      if (from_start[state] == kUnreachable or to_end[state] == kUnreachable) continue;
      if (from_start[state] + to_end[state] == best) {
        ++tiles;
        break;
      }
    }
  }
  s::cout << tiles << '\n';
}
