#ifndef DAY16_H
#define DAY16_H

#include <algorithm>
#include <functional>
#include <limits>
#include <queue>
#include <utility>
#include <vector>

#include <aliases.h>
#include <grid.h>

inline constexpr long long kUnreachable = s::numeric_limits<long long>::max();
inline constexpr size_t kEast = 1;  // index into kNeighbors4

// A reindeer state: standing on a cell facing a heading.
inline size_t state_of(const Grid& grid, Cell cell, size_t heading) {
  return (cell.row * grid[0].size() + cell.col) * kNeighbors4.size() + heading;
}

// Lowest score from any of `sources` to every state; stepping forward costs
// 1 and a quarter turn costs 1000. When `backward`, steps are retraced in
// reverse, giving the lowest score from each state to the sources instead.
inline vec<long long> maze_scores(const Grid& grid, const vec<size_t>& sources, bool backward) {
  size_t width = grid[0].size();
  vec<long long> scores(grid.size() * width * kNeighbors4.size(), kUnreachable);
  using Entry = s::pair<long long, size_t>;
  s::priority_queue<Entry, vec<Entry>, s::greater<>> queue;
  for (size_t source : sources) {
    scores[source] = 0;
    queue.push({0, source});
  }
  while (not queue.empty()) {
    auto [score, state] = queue.top();
    queue.pop();
    if (score > scores[state]) continue;
    size_t heading = state % kNeighbors4.size();
    size_t index = state / kNeighbors4.size();
    Cell at{static_cast<int>(index / width), static_cast<int>(index % width)};
    auto relax = [&](size_t next, long long cost) {
      if (score + cost < scores[next]) {
        scores[next] = score + cost;
        queue.push({score + cost, next});
      }
    };
    Offset dir = kNeighbors4[heading];
    int sign = backward ? -1 : 1;
    Cell ahead{at.row + sign * dir.dr, at.col + sign * dir.dc};
    if (in_bounds(grid, ahead.row, ahead.col) and grid[ahead.row][ahead.col] != '#') {
      relax(state_of(grid, ahead, heading), 1);
    }
    relax(state_of(grid, at, (heading + 1) % kNeighbors4.size()), 1000);
    relax(state_of(grid, at, (heading + kNeighbors4.size() - 1) % kNeighbors4.size()), 1000);
  }
  return scores;
}

// Start state facing east.
inline vec<size_t> maze_start(const Grid& grid) {
  return {state_of(grid, *find_cell(grid, 'S'), kEast)};
}

// The end tile in every heading.
inline vec<size_t> maze_end(const Grid& grid) {
  vec<size_t> states;
  for (size_t heading = 0; heading < kNeighbors4.size(); ++heading) {
    states.push_back(state_of(grid, *find_cell(grid, 'E'), heading));
  }
  return states;
}

inline long long best_score(const vec<long long>& scores, const vec<size_t>& states) {
  long long best = kUnreachable;
  for (size_t state : states) best = s::min(best, scores[state]);
  return best;
}

#endif  // DAY16_H
