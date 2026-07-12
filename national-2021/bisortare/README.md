# Bisortare

**Contest:** Romanian National Olympiad of Informatics - National Stage 2021
**Level:** Grades 11-12

## Problem Summary

Given a permutation of 1..N, define `BestK` as the minimum number of adjacent swaps needed to make the array decreasing on `[1..K]` and increasing on `[K..N]` (a valley). Two subtasks: compute `BestK` for one given K, or for all K from 1 to N.

## Approach

For a fixed K, the cost only depends on which elements end up in the left block (`[1..K]`) versus the right block (`[K..N]`) and not on their exact positions within each block. We can first observe that the value `1` must always be at the bottom of the valley. Another remark we can make is that in order to make an ascending/descending sequence in either direction, the number of swaps we need to make is exactly the sum of the inversions of each element. So the problem becomes: pick the best elements to go left, so that we keep the sum minimized.

For each element `i`, using a **binary indexed tree**, we compute:
- `inv[i].dr` = number of elements to the right of `i` that are smaller (will be used to compute the cost of a ascending sequence)
- `inv[i].st` = number of elements to the left of `i` that are smaller (will be used to compute the cost of a descending sequence)

`Best[1]` (K=1, whole array ascending) = sum of all `inv[i].dr` (the standard inversion count).

For any other element (except `1`, which always sits at the valley with 0 inversions either way), define `dif[i] = inv[i].st - inv[i].dr`. This is how much the total cost changes if `i` is moved from the right block into the left block.

To get `Best_K`, we need to choose K-1 elements to put in the left block, and we want the cheapest possible choice. So we sort `dif` and take the K-1 smallest values. This always gives the optimal set for that K, and `Best_K` can be computed in one pass of the array, for all K. That is because we keep adding in ascending order so it is a sum of prefixes.

`Best[i] = Best[i-1] + dif_sorted[i-1]` gives all `BestK` values with one sort and one prefix sum.

**Complexity:** O(N log N)