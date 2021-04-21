#include <bits/stdc++.h>
using namespace std;
// Mo's algorithm (莫队算法), solve m offline queries on array of length n in O(n sqrt(m))
struct MO {
    int n, m=0;
    struct node {
        int l, r, id;
    };
    vector<node> query;
    MO(int _n) : n(_n) {}
 
    void add_query(int l, int r) {
        query.push_back({l, r, m++});
    }
 
    template<typename F>
    vector<int> solve(F&& move) {
        const int BLOCK_SIZE = (n<=m ? ceil(sqrt(n)) : n/ceil(sqrt(m)));
        sort(query.begin(), query.end(), [&](const node& lhs, const node& rhs) {
            if (lhs.l / BLOCK_SIZE != rhs.l / BLOCK_SIZE) return lhs.l < rhs.l;
            return ((lhs.l / BLOCK_SIZE) & 1) ? lhs.r < rhs.r : lhs.r > rhs.r;
        });
        vector<int> ans(m);
        int l=0, r=-1, cur=0;
        for (const auto& [ql, qr, id] : query) {
            while (l > ql) move(--l, 1, cur);
            while (r < qr) move(++r, 1, cur);
            while (l < ql) move(l++, -1, cur);
            while (r > qr) move(r--, -1, cur);
            ans[id]=cur;
        }
        return ans;
    }
};

// example: find the most occurrence in ranges
int main() {
    int n, q;
    MO mo(n);
    vector<int> a(n);
    vector<int> counter(n+1), freq(3e5+1);
    auto ans=mo.solve([&](int i, int dir, int& cur) {
        int val=a[i];
        int c=freq[val];
        counter[c]--;
        if (dir==1) {
            freq[val]++;
            counter[freq[val]]++;
            cur=max(cur, freq[val]);
        } else {
            freq[val]--;
            counter[freq[val]]++;
            if (counter[cur]==0) cur--;
        }
    });
}
