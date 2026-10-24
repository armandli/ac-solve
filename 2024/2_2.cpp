#include <algorithm>
#include <iostream>

#include <aliases.h>
#include <day2.h>

// Safe as is, or after dropping any one level.
bool dampened_safe(const vec<int>& levels) {
  if (safe(levels)) return true;
  for (size_t skip = 0; skip < levels.size(); ++skip) {
    vec<int> rest = levels;
    rest.erase(rest.begin() + skip);
    if (safe(rest)) return true;
  }
  return false;
}

int main() {
  s::cout << sr::count_if(read_reports(s::cin), dampened_safe) << '\n';
}
