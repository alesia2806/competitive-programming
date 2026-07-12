# Acoperire

**Contest:** Romanian National Olympiad of Informatics - County Stage 2024
**Level:** Grades 11-12

## Problem Summary

Given N initial intervals, create at most K "covering intervals" such that every initial interval is covered (intersection with at least one covering interval has length >= half the initial interval's length). For each query K, find the minimum possible length of the longest covering interval, and output the lexicographically smallest solution achieving it.

We can notice that the covering conditions is satisfied if the covering intervals length `l >= half the initial interval's length` and the covering interval includes the midpoint of the initial interval.

## Approach

**Hint from problem statement:** Since it's asking for a minimum of the maximum covering interval, it's most probably solved by binary search of the result. 

**Simplification:** We can multiply all coordinates by 2 to avoid fractions. A covering interval `[m-l, m]` (with its right end at the midpoint `m`) covers all initial intervals whose midpoints are within `l` of `m`.

**Binary search** on the answer `l` (the half-length in doubled coordinates). For a given `l`, a greedy sweep checks feasibility: sort intervals by midpoint descending, greedily cover as many as possible with each covering interval.

We then sort in descending order by midpoint to obtain the lexicographically smallest solution (which is given when the last covering interval ends in the midpoint of the last initial interval).

**Important edge case:** Since we're using doubled coordinates, we'll be outputing their half and also `0.5` whenever is the case. However, the number **-1 will output 0.5 without special handling, so it loses its sign**. In order to fix that, we have to check if the coordinate is -1.

**Complexity:** O(N log N) for the initial sort + O(Q * N * log(NMAX)) for the binary searches (each valid() call being O(N))
