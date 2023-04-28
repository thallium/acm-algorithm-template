#pragma once
#include <vector>

struct Prime {
    std::vector<int> primes, mn_factor;
    Prime(int N) {
        mn_factor.resize(N + 1);
        for (int i = 2; i <= N; ++i) {
            if (mn_factor[i] == 0) {
                primes.push_back(i);
                mn_factor[i] = i;
            }
            for (auto p : primes) {
                if ((long long)i * p > N) break;
                mn_factor[i * p] = p;
                if (i % p == 0) break;
            }
        }
    }

    bool is_prime(int n) {
        return mn_factor[n] == n;
    }

    // Factors n in O(log(n)) time
    std::vector<std::pair<int, int>> factor(int n) {
        std::vector<std::pair<int, int>> factors;
        while (n > 1) {
            int fac = mn_factor[n], cnt = 0;
            while (n % fac == 0) {
                cnt++;
                n /= fac;
            }
            factors.emplace_back(fac, cnt);
        }
        return factors;
    };
};
