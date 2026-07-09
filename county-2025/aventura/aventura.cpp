#include <bits/stdc++.h>

#define ll long long

using namespace std;

ifstream fin("aventura.in");
ofstream fout("aventura.out");

const int LMAX = 500005;
const int MOD = 1000000007;

int grad[LMAX];

void solve() {
    int n, k, ans = 0, x;
    fin>>n;
    vector<int> L[n + 5];
    queue<int> q;
    for (int i = 1; i <= n; i++) {
        fin>>k;
        if (!k) q.push(i), ans++;
        grad[i] = k;
        while (k--) {
            fin>>x;
            L[x].push_back(i);
        }
    }
    while (!q.empty()) {
        int node = q.front();
        q.pop();
        for (int vec : L[node]) {
            grad[vec]--;
            if (!grad[vec]) {
                q.push(vec);
                ans++;
            }
        }
    }
    for (int i = 0; i <= n; i++) grad[i] = 0;
    fout<<ans<<"\n";
}


int main() {
    int t, n, x, y;
    fin>>t;
    while (t--) {
        solve();
    }


    fin.close();
    fout.close();
    return 0;
}
