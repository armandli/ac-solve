#ifndef DAY6_H
#define DAY6_H

#include <algorithm>
#include <istream>
#include <string>
#include <vector>

#include <aliases.h>
#include <input.h>

// One problem's slice of the worksheet: the digit rows, padded to equal width,
// and the operator found under them.
struct Problem {
  char op;
  vec<str> rows;
};

// Problems are separated by columns made only of spaces.
inline vec<Problem> read_worksheet(s::istream& in) {
  vec<str> lines = read_lines(in);
  while (not lines.empty() and trim(lines.back()).empty()) lines.pop_back();
  size_t width = 0;
  for (const str& line : lines) width = s::max(width, line.size());
  for (str& line : lines) line.resize(width, ' ');

  auto blank_column = [&](size_t col) {
    return sr::all_of(lines, [&](const str& line) { return line[col] == ' '; });
  };
  vec<Problem> problems;
  for (size_t col = 0; col < width;) {
    if (blank_column(col)) {
      ++col;
      continue;
    }
    size_t end = col;
    while (end < width and not blank_column(end)) ++end;
    Problem problem{trim(strv(lines.back()).substr(col, end - col))[0], {}};
    for (size_t row = 0; row + 1 < lines.size(); ++row) {
      problem.rows.push_back(lines[row].substr(col, end - col));
    }
    problems.push_back(s::move(problem));
    col = end;
  }
  return problems;
}

inline long long evaluate(char op, const vec<long long>& numbers) {
  long long result = op == '*' ? 1 : 0;
  for (long long number : numbers) result = op == '*' ? result * number : result + number;
  return result;
}

#endif  // DAY6_H
