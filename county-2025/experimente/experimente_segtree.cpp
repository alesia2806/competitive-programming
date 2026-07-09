#include <bits/stdc++.h>

#define ll long long

using namespace std;

ifstream fin("experimente.in");
ofstream fout("experimente.out");

const int LMAX = 5005;
const int INF = 0x3f3f3f3f;
const ll MOD = 1000000007;

struct node{
    node* nod_s, *nod_d;
    int val;
    bool lazy;
    node(int d) {
        nod_s = nullptr;
        nod_d = nullptr;
        val = d;
        lazy = 0;
    }
};

void propagate(node* nod, int st, int dr) {
    int mij = ((st + dr)>>1);
    if (!nod->nod_s) {
        nod->nod_s = new node(mij - st + 1);
    }
    if (!nod->nod_d) {
        nod->nod_d = new node(dr - mij);
    }
    if (nod->lazy) {
        nod->lazy = 0;
        nod->nod_s->lazy = nod->nod_d->lazy = 1;
        nod->nod_s->val = nod->nod_d->val = 0;
    }
}

void update(node* nod, int st, int dr, int qs, int qd) {
    propagate(nod, st, dr);
    if (qs <= st && dr <= qd) {
        nod->val = 0;
    }
    else {
        int mij = ((st + dr)>>1);
        if (qd <= mij) {
            if (nod->nod_s->val != 0) update(nod->nod_s, st, mij, qs, qd);
        }
        else if (qs > mij) {
            if (nod->nod_d->val != 0) update(nod->nod_d, mij + 1, dr, qs, qd);
        }
        else {
            if (nod->nod_s->val != 0) update(nod->nod_s, st, mij, qs, mij);
            if (nod->nod_d->val != 0) update(nod->nod_d, mij + 1, dr, mij + 1, qd);
        }
        nod->val = nod->nod_s->val + nod->nod_d->val;
    }
}

int main() {
    int n, m, a, b;
    fin>>n>>m;
    node* root = new node(n);
    while (m--) {
        fin>>a>>b;
        a = (a + root->val)%n;
        b = (b + root->val)%n;
        if (a <= b) {
            if (a > 0) update(root, 0, n - 1, 0, a - 1);
            if (b < n - 1) update(root, 0, n - 1, b + 1, n - 1);
        }
        else {
            if (b + 1 <= a - 1) update(root, 0, n - 1, b + 1, a - 1);
        }
        fout<<root->val<<"\n";
    }


    fin.close();
    fout.close();
    return 0;
}
