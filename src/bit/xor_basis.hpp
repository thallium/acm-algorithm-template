#include <limits>
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

    T max_value(T start = 0) {
        for (int i = B - 1; i >= 0; i--) {
            if (basis[i]) {
                start = max(start, start ^ basis[i]);
            }
        }
        return start;
    }

    // return the kth smallest element in the vector space
    T kth(long long k) {
        assert(k > 0 && k <= (1LL << sz));
        T ans{};
        long long tot = 1LL << sz;
        for (int i = B - 1; i >= 0; i--) {
            if (basis[i]) {
                auto low = tot / 2;

                if ((low < k && (ans >> i & 1) == 0) || (low >= k && (ans >> i & 1)))
                    ans ^= basis[i];

                if (low < k)
                    k -= low;

                tot /= 2;
            }
        }
        return ans;
    }
};
