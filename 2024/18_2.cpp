#include <iostream>

#include <aliases.h>
#include <day18.h>
#include <dsu.h>
#include <grid.h>

int main() {
  vec<Cell> bytes = read_falling_bytes(s::cin);
  Grid grid = corrupted_memory(bytes, bytes.size());
  auto index = [](Cell cell) { return static_cast<size_t>(cell.row * kMemorySize + cell.col); };
  DisjointSet regions(kMemorySize * kMemorySize);
  auto open = [&](Cell cell) {
    grid[cell.row][cell.col] = '.';
    for (auto [dr, dc] : kNeighbors4) {
      Cell next{cell.row + dr, cell.col + dc};
      if (in_bounds(grid, next.row, next.col) and grid[next.row][next.col] == '.') {
        regions.unite(index(cell), index(next));
      }
    }
  };
  for (int row = 0; row < kMemorySize; ++row) {
    for (int col = 0; col < kMemorySize; ++col) {
      if (grid[row][col] == '.') open({row, col});
    }
  }
  // Un-corrupt bytes latest first; the one that reconnects start and exit is
  // the first that cut them apart.
  Cell exit{kMemorySize - 1, kMemorySize - 1};
  for (size_t i = bytes.size(); i-- > 0;) {
    open(bytes[i]);
    if (regions.find(index({0, 0})) == regions.find(index(exit))) {
      s::cout << bytes[i].col << ',' << bytes[i].row << '\n';
      return 0;
    }
  }
}
