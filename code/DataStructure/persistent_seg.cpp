//find the nth biggest number
#include<bits/stdc++.h>
using namespace std;
struct PST {
    int n, tot=0;
    vector<int> lc, rc, sum, roots; // left child, right child
    PST(int n_) : n(n_), lc(n<<5), rc(n<<5), sum(n<<5), roots(1) { // change the size to n<<6 if there are 2*n modification 
        build(0, n-1, roots[0]); // the initial root node is 1!
    }
    void pushup(int rt) {
        sum[rt] = sum[lc[rt]] + sum[rc[rt]];
    }
    void build(int l, int r, int& rt) {
        rt = ++tot;
        if (l == r) return;
        int mid = (l + r) >> 1;
        build(l, mid, lc[rt]);
        build(mid + 1, r, rc[rt]);
        pushup(rt);
    }
    void update(int pos, int val, int l, int r, int old, int& rt) {
        rt = ++tot;
        lc[rt] = lc[old];
        rc[rt] = rc[old];
        if (l == r) {
            sum[rt] = sum[old] + val;
            return;
        }
        int mid = (l + r) >> 1;
        if (pos <= mid) update(pos, val, l, mid, lc[old], lc[rt]);
        else update(pos, val, mid + 1, r, rc[old], rc[rt]);
        pushup(rt);
    }
    int update(int pos, int val) { // return the root of the new version
        int new_root;
        update(pos, val, 0, n-1, roots.back(), new_root);
        roots.push_back(new_root);
        return new_root;
    }
    int query(int u, int v, int l, int r, int k) {
        if (l==r) return l;
        int mid=(l+r)/2, x=sum[lc[v]]-sum[lc[u]];
        if (k<=x) return query(lc[u], lc[v], l, mid, k);
        return query(rc[u], rc[v], mid+1, r, k-x);
    }
};
int main(){
    int n, q;
    cin>>n>>q;
    vector<int> a(n);
    for (auto& x : a) cin>>x;
    auto comp=a;
    sort(comp.begin(), comp.end());
    comp.erase(unique(comp.begin(), comp.end()), comp.end());
    PST tr(comp.size());
    vector<int> roots(n+1);
    roots[0]=1;
    for (int i=0; i<n; i++) {
        int p=lower_bound(comp.begin(), comp.end(), a[i])-comp.begin();
        roots[i+1]=tr.update(p, 1);
    }
    while (q--) {
        int l, r, k;
        cin>>l>>r>>k;
        cout<<comp[tr.query(roots[l-1], roots[r], 0, comp.size()-1, k)]<<'\n';
    }
}
