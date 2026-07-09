# Cromatic

**Contest:** Romanian National Olympiad of Informatics - County Stage 2025
**Level:** Grades 11-12

## Problem Summary

Given an array `a`, define `min_k` and `max_k` as the running minimum and maximum up to index `k`. The array is *chromatic* if all intervals `[min_k, max_k]` are distinct. Observation: all elements must be distinct for this to hold (duplicate values freeze the interval).

Three subtasks:

1. **Count** chromatic permutations of `a` modulo 10^9+7
2. **Rank** a given chromatic permutation among all chromatic permutations in lexicographic order
3. **Find** the q-th chromatic permutation in lexicographic order

## Approach

While playing with building chromatic arrays, we can make an important remark. Once we've built the array up until position `i`, the element at position `i + 1` should either be the smallest element that is bigger than `a[i]`, or the biggest element that is smaller than `a[i]`. In other words, if we sort the array and obtain the sorted array `s`, the next element can either be `s[j - 1]` or `s[j + 1]`, with `j` being the position at which we find `a[i]` in `s`. That's because if we chose anything else, at some point the min/max would stop updating, since the current interval already "swallows" it. So for *almost* every element we have 2 options for its successor. The exception are the global minimum and the global maximum, which each only have a single valid successor.

**Subtask 1:** If any duplicates exist, answer is 0. Otherwise, we can arrive to a formula by fixating the global minimum/maximum. If the extreme value is in the first position, we only have one chromatic array. If it's the second one, we have 2 options for the previous element, so 2 arrays in total. If it's the third one, we have 2 options for the element at position 1, and 4 options for the element at position 0. Following this logic, we arrive to the formula for the total number of arrays: `2 * (1 + 2 + 2^2 + .. + 2^(n - 1)) = 2 * 2^(n - 2) = 2^(n - 1)`.

**Subtask 2:** Count how many elements smaller than `a[1]` exist (call it `nract`). Using the fact that the smaller elements must appear in decreasing order and the bigger ones must appear in increasing order, we iterate through the array position by position and decide, at each step, whether it took from the "smaller" branch or the "bigger" branch:
- if it's the smaller element, we already have that counted so we do nothing.
- if it's the bigger element, we add the number of possible chromatic arrays that existed if we took the other branch.

Summed across all positions, we get the rank of `a`.

**Subtask 3:** We use the same combinatorial structure, but greedily on the sorted array: at each position we check whether taking from the "smaller" side or the "bigger" side keeps us within the target rank `q`.

**Complexity:** O(N log N) for sorting; O(N*K) for combinatorics where K is small in practice.
