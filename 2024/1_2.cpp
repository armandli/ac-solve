#include <iostream>

#include <aliases.h>
#include <day1.h>

int main() {
  Lists lists = read_lists(s::cin);
  umap<long long, long long> occurrences;
  for (long long id : lists.right) ++occurrences[id];
  long long score = 0;
  for (long long id : lists.left) {
    if (auto it = occurrences.find(id); it != occurrences.end()) score += id * it->second;
  }
  s::cout << score << '\n';
}
