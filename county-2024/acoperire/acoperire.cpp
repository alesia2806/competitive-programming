#include <fstream>
#include <iostream>
#include <climits>
#include <algorithm>
#include <vector>
#include <iomanip>

using namespace std;

ifstream fin("acoperire.in");
ofstream fout("acoperire.out");

const int LMAX = 100005;
const long long NMAX = 200000005;

int n;

struct interval{
    long long st, dr, mij;
}v[LMAX];

vector<pair<long long, long long>> ans, aux;

bool cmp(interval a, interval b) {
    if (a.mij > b.mij) return true;
    return false;
}

bool valid(long long l, int k) {
    int i = 0, cnt = 1, j; // cnt --> number of intervals
    aux.clear();
    while (i < n && cnt <= k) {
        j = i + 1;
        while (j < n && v[i].mij - v[j].mij <= l) { // how many intervals can i cover?
            j++;
        }
        if (j != n) {
            cnt++;
        }
        aux.push_back({v[i].mij - l, v[i].mij});
        i = j; // from where a new interval begins
    }
    if (cnt <= k) {
        ans.clear();
        for (i = 0; i < aux.size(); i++) ans.push_back(aux[i]);
        return cnt;
    }
    else return false;
}


int main() {
    int q, k, i;
    fin>>n;
    long long l;
    l = INT_MIN;
    for (i = 0; i < n; i++) {
        fin>>v[i].st>>v[i].dr;
        v[i].st = v[i].st * 2;
        v[i].dr = v[i].dr * 2;
        v[i].mij = ((v[i].dr + v[i].st) >> 1);
        l = max(v[i].mij - v[i].st, l); // maximum lentgh between the midpoint and the left point
    }
    sort(v, v + n, cmp); // sorting in descending order so that we can get the lexicographically smallest solution
    fin>>q;
    while (q--) {
        fin>>k;
        int st, dr, mij;
        st = l - 1;
        dr = NMAX;
        while (st + 1 != dr) {
            mij = ((st + dr) >> 1);
            if (valid(mij, k)) {
                dr = mij;
            }
            else {
                st = mij;
            }
        }
        fout<<dr/2;
        if (dr%2 != 0) {
            fout<<".5";
        }
        fout<<"\n";
        fout<<ans.size()<<"\n";
        for (i = ans.size() - 1; i >= 0; i--) {
            long long x = ans[i].first;
            if (x == -1) { // important edge case
                fout<<"-0.5";
            }
            else {
                fout<<x/2;
                if (x%2 != 0) {
                    fout<<".5";
                }
            }
            fout<<" ";
            x = ans[i].second;
            if (x == -1) {
                fout<<"-0.5";
            }
            else {
                fout<<x/2;
                if (x%2 != 0) {
                    fout<<".5";
                }
            }
            fout<<"\n";
        }
        ans.clear();
    }


    fin.close();
    fout.close();
    return 0;
}
