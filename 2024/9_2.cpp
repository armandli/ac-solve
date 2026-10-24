#include <algorithm>
#include <iostream>

#include <aliases.h>
#include <day9.h>

struct Span {
  size_t pos;
  size_t len;
};

int main() {
  vec<int> blocks = read_blocks(s::cin);
  vec<Span> files;  // indexed by file ID
  vec<Span> gaps;   // in disk order
  for (size_t pos = 0; pos < blocks.size();) {
    size_t end = pos;
    while (end < blocks.size() and blocks[end] == blocks[pos]) ++end;
    if (blocks[pos] == kFree) {
      gaps.push_back({pos, end - pos});
    } else {
      files.push_back({pos, end - pos});
    }
    pos = end;
  }
  for (size_t id = files.size(); id-- > 0;) {
    Span& file = files[id];
    auto gap = sr::find_if(gaps, [&](const Span& g) { return g.len >= file.len or g.pos >= file.pos; });
    if (gap == gaps.end() or gap->pos >= file.pos) continue;
    s::fill_n(blocks.begin() + gap->pos, file.len, static_cast<int>(id));
    s::fill_n(blocks.begin() + file.pos, file.len, kFree);
    // Space a file vacates lies right of every file still to move, so it is
    // never a useful destination and the gap list need not grow.
    file.pos = gap->pos;
    gap->pos += file.len;
    gap->len -= file.len;
  }
  s::cout << checksum(blocks) << '\n';
}
