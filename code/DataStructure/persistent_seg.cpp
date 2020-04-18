//find the nth biggest number
struct PerSegTree {
    vector<int> lson, rson, sum, root;
    int tot;
    PerSegTree(int n) {
        lson = rson = sum = vector<int>(n << 5);
        root = vector<int>(n + 1);
        tot = 0;
    }
    void pushup(int rt) {
        sum[rt] = sum[lson[rt]] + sum[rson[rt]];
    }
    void build(int l, int r, int& rt) {
        rt = ++tot;
        if (l == r) return;
        int mid = (l + r) >> 1;
        build(l, mid, lson[rt]);
        build(mid + 1, r, rson[rt]);
        pushup(rt);
    }
    void update(int pos, int val, int l, int r, int old, int& rt) {
        rt = ++tot;
        lson[rt] = lson[old];
        rson[rt] = rson[old];
        if (l == r) {
            sum[rt] = sum[old] + val;
            return;
        }
        int mid = (l + r) >> 1;
        if (pos <= mid) update(pos, val, l, mid, lson[old], lson[rt]);
        else update(pos, val, mid + 1, r, rson[old], rson[rt]);
        pushup(rt);
    }
    int query(int l, int r, int old_rt, int rt) {
        if(l==r) return //sth;
        int mid=(l+r)>>1;
        //sum[rt]-sum[old_rt] is the sum of the current interval
    }
};
int main(){
    PerSegTree tr;
    tr.build(1,n,tr.root[0]);
    for1(i,n){
		int x;
		cin>>x;
		int pos=getpos(x);
        tr.update(pos,val,1,n,tr.root[i-1],tr.root[i]);
	}
	query(ver[l-1],ver[r],1,len,kth);
}
