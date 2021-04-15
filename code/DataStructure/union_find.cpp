#include <bits/stdc++.h>
using namespace std;
struct UF {
    vector<int> parent, sz;
    UF(int n) : parent(n), sz(n, 1) {
        iota(parent.begin(), parent.end(), 0);
    }

    int find(int x) {
        return parent[x]==x ? x : parent[x]=find(parent[x]);
    }

    bool join(int x, int y) {
        x=find(x), y=find(y);
        if (x==y) return false;
        if (sz[x]>sz[y]) swap(x, y);
        parent[x]=y;
        sz[y]+=sz[x];
        return true;
    }
};

