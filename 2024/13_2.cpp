#include <iostream>

#include <aliases.h>
#include <day13.h>

int main() {
  long long total = 0;
  for (ClawMachine machine : read_claw_machines(s::cin)) {
    machine.px += 10000000000000;
    machine.py += 10000000000000;
    if (opt<Presses> presses = win(machine)) total += presses->tokens();
  }
  s::cout << total << '\n';
}
