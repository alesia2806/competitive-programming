#include <fstream>
#include <iostream>
#include <climits>

using namespace std;

ifstream fin("birocratie.in");
ofstream fout("birocratie.out");

const int LMAX = 1005;

int dp[LMAX][LMAX], a[LMAX][LMAX];

int main() {
    int n, i, j, k;
    fin>>n;
    for (i = 1; i <= n; i++) {
        for (j = 1; j <= n; j++) {
            fin>>a[i][j];
        }
    }
    for (i = 0; i <= n + 1; i++) {
        for (j = 0; j <= n + 1; j++) {
            dp[i][j] = INT_MIN;
        }
    }
    dp[1][1]= a[1][1];
    int secv;
    for (k = 2; k <= 2*n - 1; k++) { // number of diagonals
        secv = INT_MIN;
        j = max(1, k + 1 - n); // the column
        for (i = min(k, n); i >= max(1, k + 1 - n); i--) { // from left to right (or going upwards)
            secv = max(secv, max(dp[i][j-1], dp[i-1][j])) + a[i][j]; // maximum sequence until the current element (either from the current diagonal or the previous one)
            dp[i][j] = secv;
            j++;
        }
        j = min(n, k);
        secv = INT_MIN;
        for (i = max(1, k + 1 - n); i <= min(k, n); i++) { // from right to left (or going downwards)
            secv = max(secv, max(dp[i][j-1], dp[i-1][j])) + a[i][j]; // maximum sequence until the current element
            dp[i][j] = max(secv, dp[i][j]);
            j--;
        }
    }
    fout<<dp[n][n];



    fin.close();
    fout.close();
    return 0;
}