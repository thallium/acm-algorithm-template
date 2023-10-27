namespace Fractorization {
    using u64 = uint64_t;
    using u128 = __uint128_t;
    using ull = unsigned long long;
    mt19937 rand(chrono::steady_clock::now().time_since_epoch().count());

    u64 binPow(u64 a, u64 b, u64 mod) {
        if (b == 0)
            return 1;
        if (b & 1)
            return (u128)a * binPow(a, b ^ 1, mod) % mod;
        return binPow((u128)a * a % mod, b >> 1, mod);
    }
    bool checkComp(u64 n, u64 a, u64 d, int s) {
        u64 x = binPow(a, d, n);
        if (x == 1 || x == n - 1)
            return false;
        for (int r = 1; r < s; r++) {
            x = (u128)x * x % n;
            if (x == n - 1)
                return false;
        }
        return true;
    }
    bool RabinMiller(u64 n) {
        if (n < 2)
            return false;
        int r = 0;
        u64 d = n - 1;
        while (!(d & 1))
            d >>= 1, r++;
        for (int a : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37}) {
            if (n == a)
                return true;
            if (checkComp(n, a, d, r))
                return false;
        }
        return true;
    }
    ull mult(ull a, ull b, ull mod) { return (u128)a * b % mod; }
    ull rho(ull n) { // wiull find a factor < n, but not necessarily prime
        if (~n & 1)
            return 2;
        ull c = rand() % n, x = rand() % n, y = x, d = 1;
        while (d == 1) {
            x = (mult(x, x, n) + c) % n;
            y = (mult(y, y, n) + c) % n;
            y = (mult(y, y, n) + c) % n;
            d = gcd(max(x, y) - min(x, y), n);
        }
        return d == n ? rho(n) : d;
    }
    vector<pair<ull, int>> factorRho(ull n) {
        map<ull, int> fact;
        function<void(ull)> factRho = [&](ull n) {
            if (n == 1)
                return;
            if (RabinMiller(n)) {
                fact[n]++;
                return;
            }
            ull factor = rho(n);
            factRho(factor);
            factRho(n / factor);
        };
        factRho(n);
        vector<pair<ull, int>> facts;
        for (auto &p : fact)
            facts.push_back(p);
        return facts;
    }
    vector<pair<int, int>> factor(int n) {
        vector<pair<int, int>> facts;
        for (int f = 2; f * f <= n; f++) {
            if (n % f == 0) {
                int c = 0;
                while (n % f == 0) {
                    n /= f;
                    c++;
                }
                facts.emplace_back(f, c);
            }
        }
        return facts;
    }
} // namespace Fractorization
using namespace Fractorization;
