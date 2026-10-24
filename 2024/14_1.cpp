#include <array>
#include <iostream>

#include <aliases.h>
#include <day14.h>

int main() {
  s::array<long long, 4> quadrants{};
  for (const Robot& robot : read_robots(s::cin)) {
    int x = wrap_position(robot.px, robot.vx, 100, kSpaceWidth);
    int y = wrap_position(robot.py, robot.vy, 100, kSpaceHeight);
    if (x == kSpaceWidth / 2 or y == kSpaceHeight / 2) continue;
    ++quadrants[(x > kSpaceWidth / 2) + 2 * (y > kSpaceHeight / 2)];
  }
  s::cout << quadrants[0] * quadrants[1] * quadrants[2] * quadrants[3] << '\n';
}
