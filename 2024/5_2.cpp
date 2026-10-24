#include <algorithm>
#include <iostream>

#include <aliases.h>
#include <day5.h>

int main() {
  PrintQueue queue = read_print_queue(s::cin);
  long long total = 0;
  for (vec<int>& update : queue.updates) {
    if (sr::is_sorted(update, PageOrder{queue})) continue;
    sr::sort(update, PageOrder{queue});
    total += update[update.size() / 2];
  }
  s::cout << total << '\n';
}
