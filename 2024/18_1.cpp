#include <iostream>

#include <aliases.h>
#include <day18.h>
#include <grid.h>

int main() {
  Grid grid = corrupted_memory(read_falling_bytes(s::cin), 1024);
  s::cout << bfs_distances(grid, {0, 0})[kMemorySize - 1][kMemorySize - 1] << '\n';
}
