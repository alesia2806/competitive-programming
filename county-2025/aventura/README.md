# Aventura

**Contest:** Romanian National Olympiad of Informatics - County Stage 2025
**Level:** Grades 11-12

## Problem Summary

A game starts at level 1. Each level `i` has a dependency list `l(i)`. It can only be completed once all levels in its list are completed. Level 1 always has an empty list. Find the maximum number of levels that can be completed.

## Approach

**Initial thoughts:** This problem can be easily solved in an optimal way by performing a *BFS*, with the initial queue of levels with empty lists. We keep track of how many dependecies have been solved per level.

- Build a reverse adjacency list: for each level `x` in `l(i)`, add an edge `x -> i` (means i is dependent on x)
- Push all nodes with in-degree 0 into a queue
- BFS: for each processed node, decrement the in-degree of its neighbours, push in the queue those that reach 0
- Answer = number of nodes processed

**Complexity:** O(N + sum of all k_i)
