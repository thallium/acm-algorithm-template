#pragma once

#include <vector>
#include <string>

template<typename T>
static std::vector<int> prefix_function(const T& s) {
    int n = (int)s.length();
    std::vector<int> pi(n);
    for (int i = 1; i < n; i++) {
        int j = pi[i - 1];
        while (j > 0 && s[i] != s[j]) j = pi[j - 1];
        if (s[i] == s[j]) j++;
        pi[i] = j;
    }
    return pi;
}
