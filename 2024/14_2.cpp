#include <iostream>
#include <limits>

#include <aliases.h>
#include <day14.h>

// The second in [0, size) at which the robots' coordinates along one axis
// bunch up the most, measured by their variance.
template<typename Coordinate>
int tightest(const vec<Robot>& robots, int size, Coordinate&& coordinate) {
  int best = 0;
  double best_variance = s::numeric_limits<double>::max();
  for (int t = 0; t < size; ++t) {
    double sum = 0;
    double squares = 0;
    for (const Robot& robot : robots) {
      double at = coordinate(robot, t);
      sum += at;
      squares += at * at;
    }
    double mean = sum / robots.size();
    double variance = squares / robots.size() - mean * mean;
    if (variance < best_variance) {
      best_variance = variance;
      best = t;
    }
  }
  return best;
}

int main() {
  vec<Robot> robots = read_robots(s::cin);
  // The tree packs robots together on both axes. Each axis repeats on its
  // own period, so find the tightest second per axis and combine them with
  // the Chinese remainder theorem (the periods are coprime).
  int tx = tightest(robots, kSpaceWidth, [](const Robot& r, int t) {
    return wrap_position(r.px, r.vx, t, kSpaceWidth);
  });
  int ty = tightest(robots, kSpaceHeight, [](const Robot& r, int t) {
    return wrap_position(r.py, r.vy, t, kSpaceHeight);
  });
  int seconds = tx;
  while (seconds % kSpaceHeight != ty) seconds += kSpaceWidth;
  s::cout << seconds << '\n';
}
