#include <bits/stdc++.h>

#define ll long long

using namespace std;

ifstream fin("zid.in");
ofstream fout("zid.out");

const int LMAX = 5005;
const int MOD = 1000000007;

ll dp[LMAX][LMAX/2], s1[2][LMAX], s2[2][LMAX], per[2][LMAX/2], x[LMAX/2], ans[LMAX/2];
int k, n;

void make_matrix() {
    int j;
    for (j = 0; j <= k; j++) {
        ans[j] = dp[n][j];
        x[j] = dp[n][j];
    }
}

void multi(ll ways1[LMAX/2], ll ways2[LMAX/2]) {
    int i, j;
    ll sol[LMAX/2];
    for (i = 0; i <= k; i++) {
        sol[i] = 0;
        for (j = 0; j <= i; j++) {
            sol[i] = (ways1[j] * ways2[i - j]%MOD + sol[i])%MOD;
        }
    }
    for (i = 0; i <= k; i++) {
        ways1[i] = sol[i];
    }
}

void fast_exp(int p) {
    while (p) {
        if (p&1) {
            multi(ans, x);
        }
        p = (p>>1);
        multi(x, x);
    }
}

int main() {
    int m;
    fin>>n>>m>>k;
    if (k%2 == 1) {
        fout<<0;
        return 0;
    }
    k = k/2;
    int i, line, j, l;
    dp[0][0] = dp[1][0] = 1;
    s1[0][0] = s1[1][0] = 1;
    s2[0][1] = s2[1][1] = 1;
    line = 0;
    // computation for one column
    for (i = 2; i <= n; i++) {
        for (j = k; j >= 0; j--) {
            dp[i][j] = (s1[line][j] + s2[line][j])%MOD;
            s2[line][j + 1] = (s2[line][j] + dp[i][j])%MOD;
            s1[1 - line][j] = (s1[1 - line][j] + dp[i][j])%MOD;
        }
        line = 1 - line;
    }
    make_matrix();
    fast_exp(m - 1);
    fout<<ans[k];

    fin.close();
    fout.close();
    return 0;
}
