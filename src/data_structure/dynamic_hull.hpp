#include <set>
/**
 * Credit:
 * https://github.com/kth-competitive-programming/kactl/blob/main/content/data-structures/LineContainer.h
 * Author: Simon Lindholm
 * Date: 2017-04-20
 * License: CC0
 * Source: own work
 * Description: Container where you can add lines of the form kx+m,
 * and query maximum values at points x. Useful for dynamic
 * programming (``convex hull trick''). Time: O(\log N) Status:
 * stress-tested
 */

struct DynamicHull {
    using ll = long long;
    struct Line {
        ll k, m;
        mutable ll p;
        bool operator<(const Line &o) const { return k < o.k; }
        bool operator<(ll x) const { return p < x; }
    };
    using iterator = std::multiset<Line>::iterator;
    std::multiset<Line, std::less<>> lines;
    const ll INF = std::numeric_limits<ll>::max();
    // (for doubles, use inf = 1/.0, div(a,b) = a/b)
    ll div(ll a, ll b) { // floored division
        return a / b - ((a ^ b) < 0 && a % b);
    }
    bool isect(iterator x, iterator y) {
        if (y == lines.end()) {
            x->p = INF;
            return false;
        }
        if (x->k == y->k) {
            x->p = x->m > y->m ? INF : -INF;
        } else {
            x->p = div(y->m - x->m, x->k - y->k);
        }
        return x->p >= y->p;
    }
    void add(ll k, ll m) {
        auto z = lines.insert({k, m, 0}), y = z++, x = y;
        while (isect(y, z)) z = lines.erase(z);
        if (x != lines.begin() && isect(--x, y)) {
            isect(x, y = lines.erase(y));
        }
        while ((y = x) != lines.begin() && (--x)->p >= y->p) {
            isect(x, lines.erase(y));
        }
    }
    ll query(ll x) {
        assert(!lines.empty());
        auto l = *lines.lower_bound(x);
        return l.k * x + l.m;
    }
};
