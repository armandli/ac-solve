#include <algorithm>
#include <iostream>
#include <vector>

#include <aliases.h>
#include <day9.h>

int main() {
  vec<Tile> tiles = read_tiles(s::cin);
  long long best = 0;
  for (size_t i = 0; i < tiles.size(); ++i) {
    for (size_t j = i + 1; j < tiles.size(); ++j) best = s::max(best, rect_area(tiles[i], tiles[j]));
  }
  s::cout << best << '\n';
}
