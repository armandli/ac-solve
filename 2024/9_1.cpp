#include <iostream>
#include <utility>

#include <aliases.h>
#include <day9.h>

int main() {
  vec<int> blocks = read_blocks(s::cin);
  if (blocks.empty()) return 0;
  // Fill the leftmost gap with the rightmost file block until they meet.
  size_t lo = 0;
  size_t hi = blocks.size() - 1;
  while (true) {
    while (lo < hi and blocks[lo] != kFree) ++lo;
    while (lo < hi and blocks[hi] == kFree) --hi;
    if (lo >= hi) break;
    s::swap(blocks[lo], blocks[hi]);
  }
  s::cout << checksum(blocks) << '\n';
}
