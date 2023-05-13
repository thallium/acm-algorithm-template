#pragma once
#include <cstdint>
#include <vector>

template<typename T>
int64_t count_inversion(const std::vector<T>& v) {
    auto a(v);
    std::vector<T> tmp(v.size());

    int64_t cnt{};
    auto merge = [&](auto& slf, int l, int r) {
        if (r - l <= 1) {
            return;
        }
        int mid = l + (r - l) / 2;
        slf(slf, l, mid);
        slf(slf, mid, r);
        for (int i = l, j = mid, k = l; k < r; k++) {
            if (j == r || (i < mid && a[i] <= a[j])) {
                tmp[k] = a[i++];
            } else {
                tmp[k] = a[j++];
                cnt += mid - i;
            }
        }
        std::copy(tmp.begin() + l, tmp.begin() + r, a.begin() + l);
    };
    merge(merge, 0, (int)v.size());
    return cnt;
}
