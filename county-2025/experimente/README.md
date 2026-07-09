# Experimente

**Contest:** Romanian National Olympiad of Informatics - County Stage 2025
**Level:** Grades 11-12

## Problem Summary

There are `n` positions (0-indexed). Each query gives two values `a` and `b` (which are offset by the previous answer, modulo n). The operation "deactivates" all positions outside the range `[a, b]` (or inside `(b, a)` if `a > b`). After each query, output the number of still-active positions. The size of the array, `N` is at most 10^9.

## Approach

I solved this problem in two different methods:

### `experimente_segtree.cpp` - Dynamic Segment Tree with Lazy Propagation
Maintains a segment tree over positions `[0, n-1]` where each node stores the count of active positions in its range. A lazy flag propagates "set to 0" operations. Each query deactivates up to two contiguous ranges. The root always holds the total active count. An ordinary segment tree approach will not get full points as it uses too much space.

**Complexity:** O(M log N) time, O(N) space (dynamic allocation avoids allocating the full tree)

### `experimente_set.cpp` - Interval Set
Maintains a set of disjoint active intervals stored as `(left, right)` pairs. Each update merges and removes overlapping intervals and inserts the new one. `inact` tracks total inactive positions; answer = `n - inact`.

**Complexity:** O(M log N) amortised - each interval is inserted and erased at most once per query on average.
