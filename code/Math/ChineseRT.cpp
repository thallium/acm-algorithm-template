#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#include "exGCD.hpp"

using ll = long long;
// Solve linear congruences equation:
// coef[i] * x % mod[i] = reminder[i] (mi don't need to be co-prime)
// M - lcm, x - smalleset integer solution
bool CRT(const vector<ll>& coef, const vector<ll> &rem, const vector<ll> &mod, ll &x, ll &lcm) {
    int n = (int)coef.size();
    x = 0, lcm = 1;
    for (int i = 0; i < n; i++) {
        ll a = coef[i] * lcm, b = rem[i] - coef[i] * x, m = mod[i];
        auto [y, t, g] = exgcd(a, m);
        if (b % g) return false;
        b /= g;
        m /= g;
        x += lcm * (__int128_t(y) * b % m);
        lcm *= m;
    }
    x = (x + lcm) % lcm;
    return true;
}
