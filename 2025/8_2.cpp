#include <iostream>
#include <vector>

#include <aliases.h>
#include <day8.h>
#include <dsu.h>

int main() {
  vec<Box> boxes = read_boxes(s::cin);
  DisjointSet circuits(boxes.size());
  for (const Link& link : links_by_distance(boxes)) {
    if (circuits.unite(link.a, link.b) and circuits.components() == 1) {
      s::cout << boxes[link.a].x * boxes[link.b].x << '\n';
      return 0;
    }
  }
  return 1;
}
