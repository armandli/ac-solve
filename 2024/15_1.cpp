#include <iostream>

#include <aliases.h>
#include <day15.h>

int main() {
  Warehouse warehouse = read_warehouse(s::cin);
  s::cout << gps_after_moves(warehouse.grid, warehouse.moves) << '\n';
}
