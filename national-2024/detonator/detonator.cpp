#include <bits/stdc++.h>

#define ll long long

using namespace std;

ifstream fin("detonator.in");
ofstream fout("detonator.out");

const int LMAX = 1005;
const int INF = 0x3f3f3f3f;
const int MOD = 666777;

bool viz[LMAX][LMAX], inQ[LMAX][LMAX];
int a[LMAX][LMAX];

struct node{
    int val, i, j;
};

bool operator < (const node &aux2, const node &aux) {
    return aux2.val < aux.val;
}

priority_queue<node> Q;

int main() {
    int q, i, j, n;
    fin>>q;
    // bordering the pyramid
    for (i = 0; i < LMAX; i++) {
        a[i][0] = INF;
        viz[i][0] = 1;
    }
    a[0][1] = INF;
    viz[0][1] = 1;
    while (q--) {
        fin>>n;
        for (i = 1; i <= n; i++) {
            for (j = 1; j <= i; j++) {
                fin>>a[i][j];
                a[i][j] = min(a[i][j], min(a[i - 1][j], a[i - 1][j - 1]));
                viz[i][j] = 0;
                inQ[i][j] = 0;
            }
            a[i][i + 1]= INF;
            viz[i][i + 1] = 1;
        }
        for (j = 1; j <= n; j++) {
            Q.push({-a[n][j], n, j});
            inQ[n][j] = 1;
        }
        int t = 1, x = INF;
        // start defusing the bombs
        while (!Q.empty() && !viz[1][1]){
            node aux = Q.top();
            aux.val = -aux.val;
            Q.pop();
            i = aux.i;
            j = aux.j;
            x = min(x, aux.val - t); // aux.val - t --> max delay of defusing this bomb
            viz[i][j] = 1;
            inQ[i][j] = 0;
            if (viz[i][j - 1] && !inQ[i - 1][j - 1]) {
                Q.push({-a[i - 1][j -1], i - 1, j - 1});
                inQ[i - 1][j - 1] = 1;
            }
            if (viz[i][j + 1] && !inQ[i - 1][j]) {
                Q.push({-a[i - 1][j], i - 1, j});
                inQ[i - 1][j] = 1;
            }
            t++;
        }
        while (!Q.empty()) {
            Q.pop();
        }
        fout<<x<<"\n";
    }



    fin.close();
    fout.close();
    return 0;
}
