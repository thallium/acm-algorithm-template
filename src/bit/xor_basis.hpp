#pragma once

#include <limits>
#include <algorithm>
#include <array>
template <typename T> struct XorBasis {
    static constexpr int B = 8 * sizeof(T);
    T basis[B]{};
    int sz = 0;

    void insert(T x) {
        for (int i = B - 1; i >= 0; i--) {
            if (x >> i == 0)
                continue;
            if (!basis[i]) {
                basis[i] = x;
                sz++;
                break;
            }
            x ^= basis[i];
        }
    }

    bool is_in(T x) {
        for (int i = B - 1; i >= 0; i--) {
            if (x >> i == 0)
                continue;
            if (!basis[i])
                return false;
            x ^= basis[i];
        }
        return true;
    }

    T max_value(T start = 0) {
        for (int i = B - 1; i >= 0; i--) {
            if (basis[i]) {
                start = max(start, start ^ basis[i]);
            }
        }
        return start;
    }

    // return the kth (0-indexed) smallest element in the vector space
    T kth(long long k) {
        assert(k >= 0 && k < (1LL << sz));
        T ans{};
        int b = sz - 1;
        for (int i = B - 1; i >= 0; i--) {
            if (basis[i]) {
                if (k >> b & 1) {
                    ans = std::max(ans, ans ^ basis[i]);
                } else {
                    ans = std::min(ans, ans ^ basis[i]);
                }
                b--;
            }
        }
        return ans;
    }
};
