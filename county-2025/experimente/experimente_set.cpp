#include <bits/stdc++.h>

#define ll long long

using namespace std;

ifstream fin("experimente.in");
ofstream fout("experimente.out");

const int LMAX = 10000005;
const int MOD = 1000003;

set<pair<int, int>> s;
int inact;

void update (int x, int y) {
    auto it = s.upper_bound({x, 0});
    int cd, cs;
    while (it != s.end() && it->second <= y) {
        inact = inact - (it->second - it->first + 1);
        s.erase(it);
        it = s.upper_bound({x, 0});
    }
    if (it != s.end() && y >= it->first) { // y is in the middle of the next interval, so (x, y) is overlapping with it --> extend y
        inact = inact - (it->second - it->first + 1);
        y = max(y, it->second);
        s.erase(it);
    }
    it = s.upper_bound({x, 0});
    if (!s.empty() && it != s.begin()) {
        it--;
        cs = it->first;
        cd = it->second;

        if (cd >= x) { // x is in the middle of the previous interval, so (x, y) is overlapping with it --> extend x
            inact = inact - (cd - cs + 1);
            s.erase(it);
            x = min(x, cs);
            y = max(y , cd);
        }
    }
    s.insert({x, y});
    inact = inact + y - x + 1;
}

int main() {
    int n, t, x, y, ans;
    fin>>n>>t;
    inact = 0;
    ans = n;
    while (t--) {
        fin>>x>>y;
        x = (x + ans)%n;
        y = (y + ans)%n;
        if (x <= y) {
            if (x > 0) update(0, x - 1);
            if (y < n - 1) update(y + 1, n - 1);
        }
        else {
            if (y + 1 <= x - 1) update(y + 1, x - 1);
        }
        ans = n - inact;
        fout<<ans<<"\n";
    }

    fin.close();
    fout.close();
    return 0;
}
