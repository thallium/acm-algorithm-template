#include <vector>

using ll = long long;
// a x + b y = gcd(a, b)
ll extgcd(ll a, ll b, ll &x, ll &y) {
    ll g = a; x = 1; y = 0;
    if (b != 0) g = extgcd(b, a % b, y, x), y -= (a / b) * x;
    return g;
}
// Solve linear congruences equation:
// a[i] * x = b[i] MOD m[i] (mi don't need to be co-prime)
// M - lcm, x - smalleset integer solution
bool chinese(const std::vector<ll> &a, const std::vector<ll> &b, const std::vector<ll> &m, ll &x, ll &M) {
    ll n = a.size();
    x = 0; M = 1;
    for(int i = 0; i < n; i++) {
        ll a_ = a[i] * M, b_ = b[i] - a[i] * x, m_ = m[i];
        ll y, t, g = extgcd(a_, m_, y, t);
        if (b_ % g) return false;
        b_ /= g; m_ /= g;
        x += M * (__int128_t(y) * __int128_t(b_) % m_);
        M *= m_;
    }
    x = (x + M) % M;
    return true;
}
