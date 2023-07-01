#pragma once
#include <array>
#include <vector>

// return [even, odd] where:
//
// even[i] is the half of the length of longest palindrome starting from the
// i-th gap, the first gap is before the first character, there are n+1 gaps.
//
// odd[i] is half of the length of longest palindrome starting from the i-th
// character.
template <typename T> std::array<std::vector<int>, 2> manacher(const T &s) {
    int n = (int)size(s);
    std::array d{std::vector<int>(n + 1), std::vector<int>(n)};

    for (int z : {0, 1}) {
        auto &p = d[z];
        for (int i = 0, l = 0, r = 0; i < n; i++) {
            int t = r - i + !z;
            if (i < r) {
                p[i] = std::min(t, p[l + t]);
            }
            int l2 = i - p[i], r2 = i + p[i] - !z;
            while (l2 && r2 + 1 < n && s[l2 - 1] == s[r2 + 1]) {
                ++p[i];
                --l2, ++r2;
            }
            if (r2 > r) {
                l = l2, r = r2;
            }
        }
    }
    return d;
}
