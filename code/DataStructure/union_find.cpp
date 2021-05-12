#include <bits/stdc++.h>
using namespace std;
struct UF {
    int n;
    vector<int> pa; // parent or size, positive number means parent, negative number means size
    explicit UF(int _n) : n(_n), pa(n, -1) {}

    int find(int x) {
        assert(0 <= x && x < n);
        return pa[x] < 0 ? x : pa[x]=find(pa[x]);
    }

    bool join(int x, int y) {
        assert(0 <= x && x < n);
        assert(0 <= y && y < n);
        x=find(x), y=find(y);
        if (x==y) return false;
        if (-pa[x] < -pa[y]) swap(x, y); // size of x is smaller than size of y
        pa[x]+=pa[y];
        pa[y]=x;
        return true;
    }

    int size(int x) {
        assert(0 <= x && x < n);
        return -pa[x];
    }

    vector<vector<int>> groups() {
        vector<int> leader(n);
        for (int i=0; i<n; i++) {
            leader[i]=find(i);
        }
        vector<vector<int>> res(n);
        for (int i=0; i<n; i++) {
            res[leader[i]].push_back(i);
        }
        res.erase(remove_if(res.begin(), res.end(),
                    [](const vector<int>& v) { return v.empty(); }), res.end());
        return res;
    }
};

