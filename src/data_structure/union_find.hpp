#pragma once
#include <vector>

struct UF {
    int n;
    std::vector<int> p; // size if negative or parent if non-negative

    UF(int n_) : n(n_), p(n, -1) {}

    int find(int x) { return p[x] < 0 ? x : p[x] = find(p[x]); }

    bool same(int x, int y) { return find(x) == find(y); }

    // calls f(x, y) meaning we're merging x into y
    template <typename F>
    bool join(int x, int y, F&& f) {
        x = find(x), y = find(y);
        if (x == y) return false;
        if (-p[x] > -p[y]) std::swap(x, y);
        p[y] += p[x];
        f(x, y);
        p[x] = y;
        return true;
    }

    bool join(int x, int y) {
        return join(x, y, [](...){});
    }

    std::vector<int> group_sizes() {
        std::vector<int> sizes;
        for (int i = 0; i < n; i++) {
            if (p[i] < 0) {
                sizes.push_back(-p[i]);
            }
        }
        return sizes;
    }

    std::vector<std::vector<int>> groups() {
        std::vector<std::vector<int>> groups(n);
        for (int i = 0; i < n; i++) {
            groups[find(i)].push_back(i);
        }

        groups.erase(
                std::remove_if(begin(groups), end(groups), [](const std::vector<int>& v) { return v.empty(); }),
                end(groups));
        return groups;
    }
};
