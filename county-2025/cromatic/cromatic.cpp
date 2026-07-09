#include <bits/stdc++.h>

#define ll long long

using namespace std;

ifstream fin("cromatic.in");
ofstream fout("cromatic.out");

const int LMAX = 300005;
const ll MOD = 1000000007;

int v[LMAX], n, sol[LMAX], p, val[LMAX];

ll comb(ll n, ll k) {
    ll ans = 1;
    for (int i = 1; i <= k; i++) {
        ans = ans*(n - i + 1)/i;
    }
    return ans;
}

void solve2() {
    // nract the position of v[1] if the array were sorted
    int nract = 0, i;
    ll ans = 1;
    for (i = 2; i <= n; i++) {
        if (v[i] < v[1]) nract++;
    }
    if (nract == 0) {
        fout<<1;
    }
    else {
        for (i = 2; i <= nract; i++) {
            ans = ans + comb(n - 1, i - 1); // i - 1 is the number of smaller elements, n - 1 is the number of positions we have available
        }
        for (i = 2; i < n && nract; i++) {
            if (v[i] > v[i - 1]) {
                ans = ans + comb(n - i, nract - 1);
            }
            else {
                nract--;
            }
        }
        fout<<ans + 1;
    }
}
void solve3() {
    sort(v + 1, v + n + 1);
    int nract, i;
    ll s = 0;
    i = 1;
    while (i <= n && s + comb(n - 1, i - 1) < p) {
        s = s + comb(n - 1, i - 1);
        i++;
    }
    sol[1] = v[i];
    nract = i - 1;
    int j = i + 1;
    for (i = 2; i <= n; i++) {
        if (nract && s + comb(n - i, nract - 1) < p) { // if I can add the "bigger" branch
            s += comb(n - i, nract - 1);
            sol[i] = v[j];
            j++;
        }
        else if (!nract) { // if there are no more smaller elements, so I must add the "bigger" branch
            sol[i] = v[j];
            j++;
        }
        else { // add the "smaller" branch
            sol[i] = v[nract];
            nract--;
        }
    }

    for (i = 1; i <= n; i++) fout<<sol[i]<<" ";
}

int main() {
    int c, i, mini, maxi;
    ll nsc = 1;
    fin>>c>>n;
    if (c == 3) fin>>p;
    fin>>v[1];
    unordered_map<int, bool> mymap;
    mymap[v[1]] = 1;
    val[1] = v[1];
    for (i = 2; i <= n; i++) {
        fin>>v[i];
        val[i] = v[i];
        if (mymap.count(v[i])) nsc = 0;
        mymap[v[i]] = 1;
        nsc = nsc*2%MOD;
    }
    if (c == 1) fout<<nsc;
    else if (c== 2){
        solve2();
    }
    else solve3();



    fin.close();
    fout.close();
    return 0;
}
