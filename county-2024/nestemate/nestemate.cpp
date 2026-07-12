#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <climits>
#include <queue>
#include <cmath>
#include <unordered_map>
using namespace std;
ifstream fin("nestemate.in");
ofstream fout("nestemate.out");

const int LMAX = 100005;
unordered_map<int, bool> inQ;
unordered_map<int, vector<int>> L;


struct triplet {
    int x, y, z;
}v[LMAX];

int solve(int a, int b, int n) {
    queue<int> q;
    inQ[a] = true;
    q.push(a);
    vector<int> dist(n + 1, -1);
    dist[a] = 0;
    while (!q.empty()) {
        int node = q.front();
        q.pop();
        if (node == b) {
            return dist[b];
        }
        for (int vec : L[v[node].x]) {
            if (!inQ[vec]) {
                inQ[vec] = true;
                dist[vec] = dist[node] + 1;
                q.push(vec);
            }
        }
		L[v[node].x].clear();
        for (int vec : L[v[node].y]) {
            if (!inQ[vec]) {
                inQ[vec] = true;
                dist[vec] = dist[node] + 1;
                q.push(vec);
            }
        }
		L[v[node].y].clear();
        for (int vec : L[v[node].z]) {
            if (!inQ[vec]) {
                inQ[vec] = true;
                dist[vec] = dist[node] + 1;
                q.push(vec);
            }
        }
		L[v[node].z].clear();
    }
    return -1;
}

void init() {
    inQ.clear();
    L.clear();
}

int main() {
    int t, n, a, b;
    fin>>t;
    while (t--) {
        fin>>n;
        fin>>a>>b;
        for (int i = 1; i <= n; i++) {
            int x, y, z;
            fin>>x>>y>>z;
            v[i] = {x, y, z};
            L[x].push_back(i);
            L[y].push_back(i);
            L[z].push_back(i);
        }
        fout<<solve(a, b, n)<<"\n";
        init();
    }

    fin.close();
    fout.close();
    return 0;
}
