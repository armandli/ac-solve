#include <algorithm>
#include <array>
#include <iostream>
#include <utility>
#include <vector>

#include <aliases.h>
#include <day9.h>

namespace {

enum struct Cell : char {
  Inside,
  Boundary,
  Outside,
};

// Sorted distinct coordinates mapped onto odd slots 1, 3, 5, ...; the even
// slots in between stand for the runs of tiles between them, and slots 0 and
// the last are a margin that is always outside the loop.
struct Axis {
  vec<long long> values;

  explicit Axis(vec<long long> coords) : values(s::move(coords)) {
    sr::sort(values);
    values.erase(sr::unique(values).begin(), values.end());
  }

  size_t slot(long long value) const {
    return 2 * (sr::lower_bound(values, value) - values.begin()) + 1;
  }
  size_t slots() const { return 2 * values.size() + 1; }

  // Slots of a and b, smaller first.
  s::pair<size_t, size_t> span(long long a, long long b) const {
    auto [lo, hi] = s::minmax(a, b);
    return {slot(lo), slot(hi)};
  }
};

}  // namespace

int main() {
  vec<Tile> tiles = read_tiles(s::cin);
  vec<long long> xs, ys;
  for (Tile tile : tiles) {
    xs.push_back(tile.x);
    ys.push_back(tile.y);
  }
  Axis ax(s::move(xs)), ay(s::move(ys));
  size_t width = ax.slots(), height = ay.slots();
  vec<vec<Cell>> cells(width, vec<Cell>(height, Cell::Inside));

  // Trace the red-green loop.
  for (size_t i = 0; i < tiles.size(); ++i) {
    Tile a = tiles[i], b = tiles[(i + 1) % tiles.size()];
    auto [x0, x1] = ax.span(a.x, b.x);
    auto [y0, y1] = ay.span(a.y, b.y);
    for (size_t x = x0; x <= x1; ++x) {
      for (size_t y = y0; y <= y1; ++y) cells[x][y] = Cell::Boundary;
    }
  }

  // Flood the outside from the margin.
  constexpr s::array<s::pair<int, int>, 4> kSteps = {{{1, 0}, {-1, 0}, {0, 1}, {0, -1}}};
  vec<s::pair<size_t, size_t>> stack = {{0, 0}};
  cells[0][0] = Cell::Outside;
  while (not stack.empty()) {
    auto [x, y] = stack.back();
    stack.pop_back();
    for (auto [dx, dy] : kSteps) {
      size_t nx = x + dx, ny = y + dy;  // wraps past 0 to a huge value
      if (nx >= width or ny >= height or cells[nx][ny] != Cell::Inside) continue;
      cells[nx][ny] = Cell::Outside;
      stack.push_back({nx, ny});
    }
  }

  // outside[x][y] counts outside cells in slots [0, x) x [0, y).
  vec<vec<int>> outside(width + 1, vec<int>(height + 1, 0));
  for (size_t x = 0; x < width; ++x) {
    for (size_t y = 0; y < height; ++y) {
      outside[x + 1][y + 1] = outside[x][y + 1] + outside[x + 1][y] - outside[x][y] +
                              (cells[x][y] == Cell::Outside ? 1 : 0);
    }
  }

  long long best = 0;
  for (size_t i = 0; i < tiles.size(); ++i) {
    for (size_t j = i + 1; j < tiles.size(); ++j) {
      long long area = rect_area(tiles[i], tiles[j]);
      if (area <= best) continue;
      auto [x0, x1] = ax.span(tiles[i].x, tiles[j].x);
      auto [y0, y1] = ay.span(tiles[i].y, tiles[j].y);
      int bad = outside[x1 + 1][y1 + 1] - outside[x0][y1 + 1] - outside[x1 + 1][y0] + outside[x0][y0];
      if (bad == 0) best = area;
    }
  }
  s::cout << best << '\n';
}
