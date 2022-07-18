// using treap to maintain a sequence that support multiple operation, index
// starts from 0!
#include<bits/stdc++.h>
mt19937 gen(chrono::high_resolution_clock::now().time_since_epoch().count());
struct data {
    long long v;
    data(long long _v = 0) : v(_v) {}
    operator bool() const { return v != 0; }
    operator int() const { return v; }
    bool operator < (const data& d) const {
        return v < d.v;
    }
};
template <typename T> struct Treap {
    struct node {
        int ch[2], sz=0;
        unsigned k=0;
        T d, sum;
        node() = default;
        node(T d_) : sz(1), k((unsigned)gen()), d(d_), sum(d_) { ch[0] = ch[1] = 0; }
    };
    vector<node> nodes;
    int root, recyc;
    Treap(int size=2e5) {
        nodes.reserve((size = max(size, 15)) + 1);
        nodes.emplace_back();
        root = recyc = 0;
    }
    inline int &ch(int rt, int r) { return nodes[rt].ch[r]; }
    int new_node(const T &d) {
        int id = (int)nodes.size();
        if (recyc) {
            id = recyc;
            if (ch(recyc, 0) && ch(recyc, 1))
                recyc = merge(ch(recyc, 0), ch(recyc, 1));
            else
                recyc = ch(recyc, ch(recyc,0) ? 0 : 1);
            nodes[id] = node(d);
        } else nodes.push_back(node(d));
        return id;
    }
    int pull(int rt) {
        node &n = nodes[rt];
        n.sz = 1 + nodes[n.ch[0]].sz + nodes[n.ch[1]].sz;
        n.sum = n.d + nodes[n.ch[0]].sum + nodes[n.ch[1]].sum;
        return rt;
    }
    int merge(int tl, int tr) {
        if (!tl) return tr;
        if (!tr) return tl;
        if (nodes[tl].k < nodes[tr].k) {
            // pushdown(tl);
            ch(tl, 1) = merge(ch(tl, 1), tr);
            return pull(tl);
        } else {
            // pushdown(tr);
            ch(tr, 0) = merge(tl, ch(tr, 0));
            return pull(tr);
        }
    }
    void split_size(int rt, int k, int &x, int &y) { // split between k-th element and (k+1)-th element
        if (!rt) {
            x = y = 0;
            return;
        }
        // pushdown(rt);
        if (nodes[ch(rt, 0)].sz > k) {
            y = rt;
            split_size(ch(rt, 0), k, x, ch(rt, 0));
        } else {
            x = rt;
            split_size(ch(rt, 1), k - nodes[ch(rt, 0)].sz - 1, ch(rt, 1), y);
        }
        pull(rt);
    }
    void split_val(int rt, const T& target, int& x, int& y) {// split into two sets such that one contains <=k and other contains >k
        if (!rt) {
            x=y=0;
            return;
        }
        if (target < nodes[rt].d) {
            y = rt;
            split_val(ch(rt, 0), target, x, ch(rt, 0));
        } else {
            x = rt;
            split_val(ch(rt, 1), target, ch(rt, 1), y);
        }
        pull(rt);
    }
    void remove(int &rt) {
        if (recyc == 0) recyc = rt;
        else recyc = merge(recyc, rt);
        rt = 0;
    }
    int order_of_key(int rt, const T& d) {
        if (rt==0) return 0;
        node& cur = nodes[rt];
        if (d <= cur.d) return order_of_key(cur.ch[0], d);
        return order_of_key(cur.ch[1], d)+nodes[cur.ch[0]].sz+1;
    }
    // interface
    int size() { return nodes[root].sz; }
    void insert(const T& v) {
        int lt, rt;
        split_val(root, v, lt, rt);
        root = merge(merge(lt, new_node(v)), rt);
    }
    bool erase(const T& v, bool all=false) {
        int lt, mt, nt, rt;
        split_val(root, v - 1, lt, mt);
        split_val(mt, v, nt, rt);
        bool found=nodes[nt].d==v;
        if (found && (all or nt==0))
            root = merge(lt, rt);
        else
            root = merge(merge(merge(lt, ch(nt, 0)), ch(nt, 1)), rt);
        return found;
    }
    int order_of_key(const T& v) {
        return order_of_key(root, v);
    }
    T find_by_order(int x)  {// order starts from 0!
        assert(x<size() && x>=-1);
        int lt, mt, rt;
        split_size(root, x, mt, rt);
        split_size(mt, x-1, lt, mt);
        root = merge(merge(lt, mt), rt);
        return nodes[mt].d;
    }
    T predecessor(const T& v) {
        return find_by_order(order_of_key(v) - 1);
    } 
    T successor(const T& v) {
        int x, y;
        split_val(root, v, x, y);
        int z=y;
        while (ch(z, 0)) z=ch(z, 0);
        root=merge(x, y);
        return nodes[z].d;
    }
};
