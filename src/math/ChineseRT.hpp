#pragma once

#include <vector>

using ll = long long;
// a x + b y = gcd(a, b)
static ll extgcd(ll a, ll b, ll &x, ll &y) {
    ll g = a; x = 1; y = 0;
    if (b != 0) g = extgcd(b, a % b, y, x), y -= (a / b) * x;
    return g;
}
// Solve linear congruences equation:
// coef[i] * x % mod[i] = reminder[i] (mi don't need to be co-prime)
// M - lcm, x - smalleset integer solution
template<typename T>
static bool chinese(const std::vector<T> &remainder, const std::vector<T> &mod, ll &x, ll &lcm, std::vector<T> coef = {}) {
    int n = remainder.size();
    if (coef.empty()) coef = std::vector<T>(n, 1);
    x = 0, lcm = 1;
    for (int i = 0; i < n; i++) {
        ll a = coef[i] * lcm, b = remainder[i] - coef[i] * x, m = mod[i];
        ll y, t, g = extgcd(a, m, y, t);
        if (b % g) return false;
        b /= g; m /= g;
        x += lcm * (__int128_t(y) * b % m);
        lcm *= m;
    }
    x = (x + lcm) % lcm;
    return true;
}
