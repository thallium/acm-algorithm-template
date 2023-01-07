#include <vector>
#include <algorithm>
using namespace std;

template <class S, auto op, auto e>
struct PST {
    struct node {
        int lc, rc;
        S d;
    };
    int n, cnt = 0;
    vector<node> t;
    vector<int> roots;
    PST() = default;
    explicit PST(int n) : PST(vector(n, e())){}
    PST(const vector<S>& v) : n((int)size(v)), roots(1) {
        t.resize(n << 5);
        build(roots[0], 0, n - 1, v);
    }
#define lc(rt) t[t[rt].lc]
#define rc(rt) t[t[rt].rc]
    void pull(int k) {
        t[k].d = lc(k).d + rc(k).d;
    }
    int new_node() {
        t.emplace_back();
        return (int)size(t) - 1;
    }
    void build(int p, int l, int r, const vector<S>& v) {
        if (l == r) {
            t[p].d = v[l];
            return;
        }
        int mid = (l + r) / 2;
        t[p].lc = new_node();
        build(t[p].lc, l, mid, v);
        t[p].rc = new_node();
        build(t[p].rc, mid + 1, r, v);
        pull(p);
    }
    template<bool set>
    void update(int p, S x, int l, int r, int old, int k) {
        t[k] = t[old];
        if (l == r) {
            if constexpr (set)
                t[k].d = x;
            else
                t[k].d = op(t[k].d, x);
            return;
        }
        int mid = (l + r) / 2;
        if (p <= mid) {
            t[k].lc = new_node();
            update<set>(p, x, l, mid, t[old].lc, t[k].lc);
        } else {
            t[k].rc = new_node();
            update<set>(p, x, mid + 1, r, t[old].rc, t[k].rc);
        }
        pull(k);
    }
    int set(int p, S x) {
        int new_root = new_node();
        update<true>(p, x, 0, n - 1, roots.back(), new_root);
        roots.push_back(new_root);
        return (int)size(roots) - 1;
    }
    int add(int p, S x) {
        int new_root = new_node();
        update<false>(p, x, 0, n - 1, roots.back(), new_root);
        roots.push_back(new_root);
        return (int)size(roots) - 1;
    }
    S get(int p, int ql, int qr, int l, int r) {
        if (ql > r || qr < l) return e();
        if (ql <= l && qr >= r) return t[p].d;
        int m = (l + r) / 2;
        return op(get(t[p].lc, ql, qr, l, m), get(t[p].rc, ql, qr, m + 1, r));
    }
    S get(int version, int l, int r) {
        return get(roots[version], l, r, 0, n - 1);
    }
};

static int op(int x, int y) {
    return x + y;
}
static int e() { return 0; }

template<typename T>
struct RangeStats : PST<int, op, e> {
    vector<T> comp;

    RangeStats(const vector<T>& a) {
        comp = a;
        sort(begin(comp), end(comp));
        comp.erase(unique(begin(comp), end(comp)), end(comp));
        n = (int)size(comp);
        t.resize(n << 5);
        roots.emplace_back();
        build(roots[0], 0, n - 1, vector(n, e()));
        for (auto x : a) {
            int p = int(lower_bound(begin(comp), end(comp), x) - begin(comp));
            add(p, 1);
        }
    }

    int kth(int u, int v, int l, int r, int k) {
        if (l == r) return l;
        int mid = (l + r) / 2, x = t[t[v].lc].d - t[t[u].lc].d;
        if (k <= x) {
            return kth(t[u].lc, t[v].lc, l, mid, k);
        }
        return kth(t[u].rc, t[v].rc, mid + 1, r, k - x);
    };
    // Returns the k-th smallest element in [l, r], k is 1-indexed.
    T kth(int l, int r, int k) {
        assert(0 <= l);
        assert(l <= r);
        assert(r + 1 < (int)roots.size());
        return comp[kth(roots[l],  roots[r + 1], 0, n - 1, k)];
    }

    int count_less_than(int u, int v, int l, int r, int target) {
        if (l == r) return l < target ? t[v].d - t[u].d : 0;
        int mid = (l + r) / 2, x = t[t[v].lc].d - t[t[u].lc].d;
        if (mid < target) {
            return x + count_less_than(t[u].rc, t[v].rc, mid + 1, r, target);
        }
        return count_less_than(t[u].lc, t[v].lc, l, mid, target);
    }

    int count_less_than(int l, int r, T target) {
        assert(0 <= l);
        assert(l <= r);
        assert(r + 1 < (int)roots.size());
        int p = int(lower_bound(begin(comp), end(comp), target) - begin(comp));
        return count_less_than(roots[l], roots[r + 1], 0, n - 1, p);
    }
};
