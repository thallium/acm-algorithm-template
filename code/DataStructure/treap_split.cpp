// using treap to maintain a sequence that support multiple operation, index
// starts from 1!
mt19937 gen(chrono::high_resolution_clock::now().time_since_epoch().count());
template <typename T> struct Treap {
    struct data {
        T v;
        data(int _v = 0) : v(_v) {}
        data operator+(const data &d) const {
            data r;
            r.v = v + d.v;
            return r;
        }
        data operator*(int t) const {
            data r;
            r.v = v * t;
            return r;
        }
        operator bool() const { return v != 0; }
        operator T() const { return v; }
    };
    struct node {
        int ch[2], sz;
        unsigned k;
        data d, sum, lz_add;
        node(int z = 1) : sz(z), k(gen()) { ch[0] = ch[1] = 0; }
    };
    vector<node> nodes;
    int root, recyc, reserve_size;
    Treap(int size=0) {
        nodes.clear();
        nodes.reserve((size = max(size, 15)) + 1);
        nodes.push_back(node(0));
        root = recyc = 0;
        reserve_size = size + 1;
    }
    void reserve() {
        if (size() >= reserve_size)
            nodes.reserve((reserve_size *= 2) + 1);
    }
    inline int &ch(int rt, int r) { return nodes[rt].ch[r]; }
    int new_node(const data &d) {
        int id = (int)nodes.size();
        if (recyc) {
            id = recyc;
            if (ch(recyc, 0) && ch(recyc, 1))
                recyc = merge(ch(recyc, 0), ch(recyc, 1));
            else
                recyc = ch(recyc, ch(recyc,0) ? 0 : 1);
            nodes[id] = node();
        } else nodes.push_back(node());
        nodes[id].d = d;
        nodes[id].sum = d;
        return id;
    }
    int update(int rt) {
        node &n = nodes[rt];
        n.sz = 1 + nodes[n.ch[0]].sz + nodes[n.ch[1]].sz;
        n.sum = n.d + nodes[n.ch[0]].sum + nodes[n.ch[1]].sum;
        return rt;
    }
    void add(int rt, const data &d) {
        node &n = nodes[rt];
        n.lz_add = n.lz_add + d;
        n.d = n.d + d;
        n.sum = n.sum + d * n.sz;
    }
    void pushdown(int rt) {
        node &n = nodes[rt];
        if (n.lz_add) {
            add(n.ch[0], n.lz_add);
            add(n.ch[1], n.lz_add);
            n.lz_add = 0;
        }
    }
    int merge(int tl, int tr) {
        if (!tl) return tr;
        if (!tr) return tl;
        if (nodes[tl].k < nodes[tr].k) {
            pushdown(tl);
            ch(tl, 1) = merge(ch(tl, 1), tr);
            return update(tl);
        } else {
            pushdown(tr);
            ch(tr, 0) = merge(tl, ch(tr, 0));
            return update(tr);
        }
    }
    void split(int rt, int k, int &x, int &y) { // split between k and k+1
        if (!rt) {
            x = y = 0;
            return;
        }
        pushdown(rt);
        if (k <= nodes[ch(rt, 0)].sz) {
            y = rt;
            split(ch(rt, 0), k, x, ch(rt, 0));
            update(y);
        } else {
            x = rt;
            split(ch(rt, 1), k - nodes[ch(rt, 0)].sz - 1, ch(rt, 1), y);
            update(x);
        }
    }
    void remove(int &rt) {
        if (recyc == 0) recyc = rt;
        else recyc = merge(recyc, rt);
        rt = 0;
    }
    // interface
    T get(int id) { return nodes[id].d; }
    int size() { return nodes[root].sz; }
    int kth(int k) { // returns the index of kth node
        int x, y, z;
        split(root, k, y, z);
        split(y, k - 1, x, y);
        root = merge(merge(x, y), z);
        return y;
    }
    void insert(int k, data v) { // insert at kth position
        int l, r;
        split(root, k - 1, l, r);
        int rt = new_node(v);
        root = merge(merge(l, rt), r);
    }
    void erase(int l, int r) {
        int x, y, z;
        split(root, r, y, z);
        split(y, l - 1, x, y);
        remove(y);
        root = merge(x, z);
    }
    void range_add(int l, int r, data v) {
        int x, y, z;
        split(root, r, y, z);
        split(y, l - 1, x, y);
        add(y, v);
        root = merge(merge(x, y), z);
    }
    T getsum(int l, int r) {
        int x, y, z;
        split(root, r, y, z);
        split(y, l - 1, x, y);
        T ret = nodes[y].sum;
        root = merge(merge(x, y), z);
        return ret;
    }
};
