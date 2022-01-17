// using treap to maintain a sequence that support multiple operation, index
// 0-based index, change pull(), add(), pushdown() according to the problem
mt19937 gen(chrono::high_resolution_clock::now().time_since_epoch().count());
template <typename T> struct Treap {
    struct node {
        int ch[2], sz;
        unsigned k;
        T d, sum, lazy;
        node(T d_, int z = 1)
            : sz(z), k((unsigned)gen()), d(d_), sum(d), lazy() {
            ch[0] = ch[1] = 0;
        }
    };
    vector<node> nodes;
    int root=0;
    Treap(int size = 2e5) {
        nodes.reserve(size);
        nodes.emplace_back(0, 0);
    }
    inline int &ch(int rt, int r) { return nodes[rt].ch[r]; }
    int new_node(const T &d) {
        int id = (int)nodes.size();
        nodes.push_back(node(d));
        return id;
    }
    int pull(int rt) {
        node &n = nodes[rt];
        n.sz = 1 + nodes[n.ch[0]].sz + nodes[n.ch[1]].sz;
        n.sum = n.d + nodes[n.ch[0]].sum + nodes[n.ch[1]].sum;
        return rt;
    }
    void add(int rt, const T &d) {
        node &n = nodes[rt];
        n.lazy = n.lazy + d;
        n.d = n.d + d;
        n.sum = n.sum + d * n.sz;
    }
    void pushdown(int rt) {
        node &n = nodes[rt];
        if (n.lazy) {
            add(n.ch[0], n.lazy);
            add(n.ch[1], n.lazy);
            n.lazy = T();
        }
    }
    int merge(int tl, int tr) {
        if (!tl) return tr;
        if (!tr) return tl;
        if (nodes[tl].k < nodes[tr].k) {
            pushdown(tl);
            ch(tl, 1) = merge(ch(tl, 1), tr);
            return pull(tl);
        } else {
            pushdown(tr);
            ch(tr, 0) = merge(tl, ch(tr, 0));
            return pull(tr);
        }
    }
    void split_by_size(int rt, int k, int &x, int &y) { // split out first k element
        if (!rt) { x = y = 0; return; }
        pushdown(rt);
        if (k <= nodes[ch(rt, 0)].sz) {
            y = rt;
            split_by_size(ch(rt, 0), k, x, ch(rt, 0));
        } else {
            x = rt;
            split_by_size(ch(rt, 1), k - nodes[ch(rt, 0)].sz - 1, ch(rt, 1), y);
        }
        pull(rt);
    }
    void split_by_val(int rt, const T& target, int& x, int& y) {// split into two sets such that one contains <=k and other contains >k
        if (!rt) { x=y=0; return; }
        pushdown(rt);
        if (target < nodes[rt].d) {
            y = rt;
            split_by_val(ch(rt, 0), target, x, ch(rt, 0));
        } else {
            x = rt;
            split_by_val(ch(rt, 1), target, ch(rt, 1), y);
        }
        pull(rt);
    }
    void remove(int &rt) { rt = 0; }
    // interface
    int size() { return nodes[root].sz; }
    const T& operator[](int k) {
        assert(k>=0 && k<size());
        int x, y, z;
        split_by_size(root, k+1, y, z);
        split_by_size(y, k, x, y);
        root = merge(merge(x, y), z);
        return nodes[y];
    }
    void insert(int k, T v) { // insert at kth position
        assert(k>=0 && k<=size());
        int l, r;
        split_by_size(root, k, l, r);
        int rt = new_node(v);
        root = merge(merge(l, rt), r);
    }
    void erase(int l, int r) {
        assert(l>=0 && l<=r && r<size());
        int x, y, z;
        split_by_size(root, r + 1, y, z);
        split_by_size(y, l, x, y);
        remove(y);
        root = merge(x, z);
    }
    void range_add(int l, int r, T v) {
        assert(l>=0 && l<=r && r<size());
        int x, y, z;
        split_by_size(root, r + 1, y, z);
        split_by_size(y, l, x, y);
        add(y, v);
        root = merge(merge(x, y), z);
    }
    T getsum(int l, int r) {
        assert(l>=0 && l<=r && r<size());
        int x, y, z;
        split_by_size(root, r + 1, y, z);
        split_by_size(y, l, x, y);
        T ret = nodes[y].sum;
        root = merge(merge(x, y), z);
        return ret;
    }
};
