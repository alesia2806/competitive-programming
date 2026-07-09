# Zid

**Contest:** Romanian National Olympiad of Informatics - National Stage 2024
**Level:** Grades 11-12

## Problem Summary

Build a wall of height N and width M using pieces of width 1. Red pieces have odd height, yellow pieces have even height. The total length of yellow pieces in each column must equal K. Count valid walls modulo 10^9+7.

Since K must be even (yellow pieces have even height), output 0 immediately if K is odd. Work with K/2 afterwards.

## Approach

**Initial thoughts:** I felt like this problem was very clearly a dynamic programming one, which I like. I first started by building the DP for one column, and then changing the code to expand the problem into 2D (which in the end didn't need changing at all, only adding one idea on top).

**DP for one column:** `dp[h][j]` = number of ways to fill a column of height `h` using yellow pieces whose total length is `2j`. At each height, the last piece placed is either: 
1. A red piece of any odd height (add to running sum `s1`).
2. A yellow piece of any even height (add to running sum `s2`). 

Maintaining `s1` and `s2` avoids recomputing them from scratch at every height, which is what keeps this part at O(NK) instead of O(N^2 * K).

**Multiple columns:** Some naive approaches here would include: *Stars and Bars* with K/2 being the sum, re-reunning the same DP with:

- **Base case:** `per[1][j] = dp[N][j]`, for `0 <= j <= K`
- **Recurrence:** for `i = 2` to `M`,
`per[i][j] = sum over l = 0..j of ( per[i-1][l] * dp[N][j-l] )`, for `0 <= j <= K`
- **Answer:** `per[M][K]`

This last idea leads to the optimization that gives 100 points. Since we're always doing the same dynamic, always using the same 'vector' (`dp[N][i]`, with N being fixed), we can implement a sort of fast matrix multiplication. The base array will be `dp[N][i]` and the DP keeps it's definition. We also observe that we can get rid of the height dimension, since we're always be working with the same height *N*. The answer will be `ans[K]`.

**Complexity:** O(NK + K^2 log M)
