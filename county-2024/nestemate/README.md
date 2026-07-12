# Nestemate

**Contest:** Romanian National Olympiad of Informatics - County Stage 2024
**Level:** Grades 11-12

## Problem Summary

Each gem has three properties (X, Y, Z). Gem A can be transformed into gem B in one step if they share at least one property value (regardless of which property). Starting from gem A, find the minimum number of transformations to reach gem B, where each intermediate state must correspond to some gem in the collection.

This is a shortest path problem on an implicit graph where nodes are gems, connected if they share a value on any property.

## Approach

BFS directly on gems, using each property value as a bucket (`L[val]`) of gems that share it. When a gem is popped out of the queue, its neighbors are all unvisited gems in `L[x]`, `L[y]`, `L[z]`.

**Bug I had:** I wasn't clearing `L[val]` after using it. Once one value gets processed, everythin else in that bucket is already visited so going through the bucket again from another gem is pointless. With many gems sharing one value this can lead up to to O(N^2) and TLEs.

**Fix:** clear each bucket right after the loop over it OR keep a map and mark each value as visited (clearly the first option is more space efficient).

**Complexity:** O(N) per test case