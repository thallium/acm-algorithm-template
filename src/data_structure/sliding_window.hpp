#pragma once

#include <functional>
#include <queue>

template<typename T, typename compare = std::less<T>>
struct SlidingWindow {
    const int k; // width of the window
    std::deque<std::pair<int, T>> q;
    compare cmp;
    explicit SlidingWindow(int k_) : k(k_), cmp() {}
    void add(int i, T x) {
        while (!q.empty() && !cmp(q.back().second, x)) q.pop_back();
        q.emplace_back(i, x);
        while (q.front().first <= i - k) q.pop_front();
    }
    T get() { return q.front().second; }
};
