# Birocratie

**Contest:** Romanian National Olympiad of Informatics - County Stage 2024
**Level:** Grades 11-12

## Problem Summary

Navigate an N*N grid from (1,1) to (N,N). Allowed moves: right, down, and both diagonals `(i,j)->(i+1,j-1)` and `(i,j)->(i-1,j+1)`. It is not allowed to revisit a cell. Each cell has a value (positive or negative). Maximise the total sum along the path.

## Approach

**Key observation:** since we can't revisit cells, that means that on a diagonal we can either go *only up* or go *only down*. After that, we always move to the next diagonal. So, we simulate each scenario and choose for each element the best sequence, which is either:
- the sequence coming from the current diagonal
- the sequence coming from the previous diagonal

The answer is `dp[n][n]`.

**Complexity:** O(N^2)
