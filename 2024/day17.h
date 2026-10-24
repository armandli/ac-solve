#ifndef DAY17_H
#define DAY17_H

#include <istream>
#include <vector>

#include <aliases.h>
#include <input.h>

struct Computer {
  long long a, b, c;
  vec<int> program;
};

// Registers A, B and C, then the comma-separated program.
inline Computer read_computer(s::istream& in) {
  vec<long long> numbers = extract_numbers(read_all(in));
  return {numbers[0], numbers[1], numbers[2], vec<int>(numbers.begin() + 3, numbers.end())};
}

// Everything the program outputs before halting.
inline vec<int> run(const vec<int>& program, long long a, long long b, long long c) {
  vec<int> output;
  size_t ip = 0;
  while (ip + 1 < program.size()) {
    int opcode = program[ip];
    int literal = program[ip + 1];
    long long combo = literal < 4 ? literal : literal == 4 ? a : literal == 5 ? b : c;
    ip += 2;
    switch (opcode) {
      case 0: a >>= combo; break;
      case 1: b ^= literal; break;
      case 2: b = combo % 8; break;
      case 3: if (a != 0) ip = literal; break;
      case 4: b ^= c; break;
      case 5: output.push_back(static_cast<int>(combo % 8)); break;
      case 6: b = a >> combo; break;
      case 7: c = a >> combo; break;
    }
  }
  return output;
}

#endif  // DAY17_H
