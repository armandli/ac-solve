#include <algorithm>
#include <functional>
#include <iostream>
#include <vector>

#include <aliases.h>
#include <day8.h>
#include <dsu.h>

int main() {
  vec<Box> boxes = read_boxes(s::cin);
  // The puzzle connects 1000 pairs; its 20-box example connects only 10.
  size_t connections = boxes.size() <= 20 ? 10 : 1000;
  vec<Link> links = links_by_distance(boxes);
  DisjointSet circuits(boxes.size());
  for (size_t i = 0; i < s::min(connections, links.size()); ++i) {
    circuits.unite(links[i].a, links[i].b);
  }
  vec<long long> sizes;
  for (size_t box = 0; box < boxes.size(); ++box) {
    if (circuits.find(box) == box) sizes.push_back(circuits.size(box));
  }
  sr::sort(sizes, s::greater{});
  long long product = 1;
  for (size_t i = 0; i < s::min<size_t>(3, sizes.size()); ++i) product *= sizes[i];
  s::cout << product << '\n';
}
