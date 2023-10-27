#include<bits/stdc++.h>
using ll = long long;
using namespace std;
// Returns {x, y, g} which is a solution to a * x + b * y = g = gcd(a, b)
static array<ll, 3> exgcd(ll a, ll b) {
    if (b == 0) return {1, 0, a};
    auto [x, y, g] = exgcd(b, a % b);
    return {y, x - a / b * y, g};
}

/*
 * Solves a * x + b * y = c, equivalently a * x = c (mod b)
 * returns {x, y, g} where x is the smallest non-negative solution
 * and g is gcd(a, b), or returns {} if the solution doesn't exist
 * all solutions: x = x0 + k * b / g, y = y0 - k * a / g
 * smallest non-negative x = (x0 % t + t) % t, where t = b / g
 */
static array<ll, 3> liEu(ll a, ll b, ll c) {
    auto [x, y, g] = exgcd(a, b);
    if (c % g != 0) return {};
    // smallest positive x:
    int64_t t = b / g;
    x = (x * ((c / g) % t) % t + t) % t;
    y = (c - a * x) / b;
    return std::array{x, y, g};
}
