//find the nth biggest number
#include<bits/stdc++.h>
using namespace std;
struct PST {
    int n, tot=0;
    struct node {
        int lc, rc, sum;
    };
    vector<node> t;
    vector<int> roots; // left child, right child
    PST(int n_) : n(n_), t(n<<5), roots(1) { // change the size to n<<6 if there are 2*n modification 
        build(0, n-1, roots[0]); // the initial root node is 1!
    }
#define lc(rt) t[t[rt].lc]
#define rc(rt) t[t[rt].rc]
    void pushup(int rt) {
        t[rt].sum = lc(rt).sum + rc(rt).sum;
    }
    void build(int l, int r, int& rt) {
        rt = ++tot;
        if (l == r) return;
        int mid = (l + r) >> 1;
        build(l, mid, t[rt].lc);
        build(mid + 1, r, t[rt].rc);
        pushup(rt);
    }
    void update(int pos, int val, int l, int r, int old, int& rt) {
        rt = ++tot;
        t[rt] = t[old];
        if (l == r) {
            t[rt].sum = t[old].sum + val;
            return;
        }
        int mid = (l + r) >> 1;
        if (pos <= mid) update(pos, val, l, mid, t[old].lc, t[rt].lc);
        else update(pos, val, mid + 1, r, t[old].rc, t[rt].rc);
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
        int mid=(l+r)/2, x=lc(v).sum-lc(u).sum;
        if (k<=x) return query(t[u].lc, t[v].lc, l, mid, k);
        return query(t[u].rc, t[v].rc, mid+1, r, k-x);
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
