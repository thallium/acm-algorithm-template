#include <vector>

template <typename T> struct Binomial {
    // using T = long long;
    std::vector<std::vector<T>> binom;
    Binomial(int n) : binom(n + 1, std::vector<T>(n + 1)) {
        binom[0][0] = 1;
        for (int i = 1; i <= n; i++) {
            binom[i][0] = binom[i][i] = 1;
            for (int j = 1; j < i; j++)
                binom[i][j] = binom[i - 1][j] + binom[i - 1][j - 1];
        }
    }

    T C(int n, int m) { // n choose m
        if (m < 0 || m > n)
            return T{};
        return binom[n][m];
    }
};
