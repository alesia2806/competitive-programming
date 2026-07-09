# Detonator

**Contest:** Romanian National Olympiad of Informatics - National Stage 2024
**Level:** Grades 11-12

## Problem Summary

A pyramid of N levels: bomb `B[i][j]` explodes at time `T[i][j]`. To defuse `B[i][j]`, its two children `B[i+1][j]` and `B[i+1][j+1]` must be defused first (the bottom level has no constraint). Defusing takes 1 second each. Find the maximum delay X such that if you start X seconds late (replacing each `T[i][j]` with `T[i][j] - X`), defusal is still possible. The delay can also be negative.

## Approach

**Initial thoughts:** This problem screamed a heap approach, but I was conflicted at first. You're restricted to only the bottom row initially, but choosing the minimum bomb isn't always the most effective move: above it there could be a bomb that explodes really late, while above a bomb that *isn't* the minimum, there could sit one that explodes quite early. I tried calculating some kind of profit based on 2 consecutive rows, but to actually get the best result, you need to take all of them into account at once.

**Then, a subtask gave me a big hint:**

One subtask restricted the input to:

- $N \le 50$, $|X| \le 10$
- $T_{i,j} \ge \max(T_{i+1,j},\, T_{i+1,j+1})$ for all $1 \le j \le i < N$

Under this constraint, the problem was much easier and my heap solution worked, because we don't have to worry about what lies above the bombs. The values are increasing from the bottom up. So, my plan became: transform every input into this shape.

**Preprocessing:** For each cell, cap its time by the minimum of its two parents' times (the bombs it unlocks). A bomb can't be useful if a parent explodes first anyway. 

**Greedy simulation with a min-heap:** Process bombs in order of increasing available time. At each step `t`, the bomb being processed must satisfy `T[i][j] - t >= X`. A bomb becomes available once both its children have been processed. Track the minimum `T[i][j] - t` across all processed bombs. That minimum is the answer X.

**Complexity:** O(N^2 log N) per test
