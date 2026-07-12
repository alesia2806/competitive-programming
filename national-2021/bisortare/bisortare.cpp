#include <iostream>
#include <fstream>
#include <cstring>
#include <set>
#include <algorithm>
#define int long long

using namespace std;

const int LMAX = 100005;

int aib[LMAX], v[LMAX], best[LMAX], dif[LMAX], n;
struct parti{
    int st, dr;
}inv[LMAX]; // nr of elements to the left of i that are smllar than i, and number of elements to the right of i that are smaller than i

int query(int pos) {
    int s = 0;
    for (int i = pos; i > 0; i -= (i&(-i))) {
        s += aib[i];
    }
    return s;
}

void update(int pos) {
    for (int i = pos; i <= n; i += (i&(-i))) {
        aib[i] += 1;
    }
}

signed main()
{
    int c, k, i;
    cin>>c>>n>>k;
    for (i = 1; i <= n; i++) {
        cin>>v[i];
    }
    for (i = n; i > 0; i--) { // right of i
        inv[i].dr = query(v[i]);
        update(v[i]);
    }
    for (i = 0; i <= n; i++) aib[i] = 0;
    int index = 1;
    for (i = 1; i <= n; i++) { // left of i
        inv[i].st = query(v[i]);
        update(v[i]);
        if (v[i] != 1) {
            dif[index] = inv[i].st - inv[i].dr;
            index++;
        }
    }

    sort(dif + 1, dif + index); // sorting for greedy, so that we always take the best possible candidate for moving to the left

    for (i = 1; i <= n; i++) {
        best[1] += inv[i].dr; // all the numbers are in ascending order. the amount of operations we need to perform is the total inversions
    }
    for (i = 2; i <= n; i++) {
        best[i] = best[i - 1] + dif[i-1]; // at best[i] we will have the easiest to move i - 1 elements to the left side
    }
    // we will keep adding inv[i].st and deleting inv[i].dr and at the end, best[n] will be the total sum of inv[i].st

    if (c == 1) {
        cout<<best[k];
    }
    else {
        for (i = 1; i <= n; i++) {
            cout<<best[i]<<" ";
        }
    }



    return 0;
}