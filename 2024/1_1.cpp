#include <algorithm>
#include <cstdlib>
#include <iostream>

#include <aliases.h>
#include <day1.h>

int main() {
  Lists lists = read_lists(s::cin);
  sr::sort(lists.left);
  sr::sort(lists.right);
  long long total = 0;
  for (size_t i = 0; i < lists.left.size(); ++i) total += s::llabs(lists.left[i] - lists.right[i]);
  s::cout << total << '\n';
}
