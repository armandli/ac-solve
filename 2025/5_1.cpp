#include <algorithm>
#include <iostream>

#include <aliases.h>
#include <day5.h>

int main() {
  Database db = read_database(s::cin);
  long long fresh = sr::count_if(db.available, [&](long long id) {
    // First merged range ending at or after id is the only one that can hold it.
    auto it = sr::lower_bound(db.fresh, id, {}, &Interval::hi);
    return it != db.fresh.end() and it->contains(id);
  });
  s::cout << fresh << '\n';
}
