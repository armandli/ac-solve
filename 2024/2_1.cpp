#include <algorithm>
#include <iostream>

#include <aliases.h>
#include <day2.h>

int main() {
  s::cout << sr::count_if(read_reports(s::cin), safe) << '\n';
}
