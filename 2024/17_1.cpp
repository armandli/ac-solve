#include <iostream>

#include <aliases.h>
#include <day17.h>

int main() {
  Computer computer = read_computer(s::cin);
  vec<int> output = run(computer.program, computer.a, computer.b, computer.c);
  for (size_t i = 0; i < output.size(); ++i) {
    s::cout << (i ? "," : "") << output[i];
  }
  s::cout << '\n';
}
