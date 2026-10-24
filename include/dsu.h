#ifndef DSU_H
#define DSU_H

#include <numeric>
#include <utility>
#include <vector>

#include <aliases.h>

// Union-find over 0..n-1 with path halving and union by size.
struct DisjointSet {
  explicit DisjointSet(size_t n) : parent_(n), size_(n, 1), components_(n) {
    s::iota(parent_.begin(), parent_.end(), size_t{0});
  }

  size_t find(size_t x) {
    while (parent_[x] != x) {
      parent_[x] = parent_[parent_[x]];
      x = parent_[x];
    }
    return x;
  }

  // Returns false when a and b were already in the same set.
  bool unite(size_t a, size_t b) {
    a = find(a);
    b = find(b);
    if (a == b) return false;
    if (size_[a] < size_[b]) s::swap(a, b);
    parent_[b] = a;
    size_[a] += size_[b];
    --components_;
    return true;
  }

  // Size of the set containing x.
  size_t size(size_t x) { return size_[find(x)]; }
  size_t components() const { return components_; }

private:
  vec<size_t> parent_;
  vec<size_t> size_;
  size_t components_;
};

#endif  // DSU_H
