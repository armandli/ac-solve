#include <iostream>

#include <aliases.h>
#include <day13.h>

int main() {
  long long total = 0;
  for (const ClawMachine& machine : read_claw_machines(s::cin)) {
    opt<Presses> presses = win(machine);
    if (presses and presses->a <= 100 and presses->b <= 100) total += presses->tokens();
  }
  s::cout << total << '\n';
}
