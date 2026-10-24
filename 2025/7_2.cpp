#include <iostream>

#include <aliases.h>
#include <day7.h>
#include <grid.h>

int main() {
  s::cout << trace_beams(read_grid(s::cin)).timelines << '\n';
}
