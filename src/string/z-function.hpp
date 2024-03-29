#pragma once

// In other words, z[i] is the length of the longest common prefix between s and the suffix of s starting at i.
#include <vector>

template<typename T>
static std::vector<int> z_function(const T& s) {
    int n = (int)s.size();
    std::vector<int> z(n);
    for (int i = 1, l = 0, r = 0; i < n; ++i) {
        if (i <= r) z[i] = std::min(r - i + 1, z[i - l]);
        while (i + z[i] < n && s[z[i]] == s[i + z[i]]) ++z[i];
        if (i + z[i] - 1 > r) l = i, r = i + z[i] - 1;
    }
    return z;
}
