#include <deque>
// monotonic_dp_hull enables you to do the following two operations in
// amortized O(1) time:
// 1. Insert a line (k, b) into the structure. k must be non-decreasing.
// 2. For any value of x, query the maximum value of k * x + b. x must
// be non-decreasing.
// Note:
// 1. if slope and/or query is non-increasing, change the order of
// insertion or operation on the other side of the queue
// 2. if slope and/or query is in arbitrary order, use line_container
// instead which has complexity of O(log n) per operation
struct monotonic_dp_hull {
    using ll = long long;
    struct line {
        ll k, b;
        ll eval(ll x) { return k * x + b; }
    };

    bool bad(const line &a, const line &b, const line &c) {
        return (c.b - a.b) * (a.k - b.k) <= (b.b - a.b) * (a.k - c.k);
    }

    std::deque<line> lines;

    void insert(ll k, ll b) {
        assert(lines.empty() ||
               k >= lines.back().k); // ensure slope is monotonic
        line cur{k, b};
        while (lines.size() >= 2 && bad(lines.rbegin()[1], lines.back(), cur))
            lines.pop_back();
        lines.push_back(cur);
    }

    ll query(ll x) {
        assert(!lines.empty());
        while (lines.size() >= 2 && lines[0].eval(x) <= lines[1].eval(x))
            lines.pop_front();
        return lines[0].eval(x);
    }
};
