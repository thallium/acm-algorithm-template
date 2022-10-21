#include <array>
#include <cstdint>
#include <optional>
//   {g, x, y}: a * x + b * y = gcd(a, b)
std::array<int64_t, 3> exgcd(int64_t a, int64_t b) {
    if (b == 0) return {a, 1, 0};
    auto [g, x, y] = exgcd(b, a % b);
    return {g, y, x - a / b * y};
}
/*
solves a * x + b * y = c, equivalently a * x = c (mod b)
all solutions: x = x0 + b / g * k, y = y0 - a / g * k
smallest non-negative x = (x0 % t + t) % t, where t = b / g
*/
std::optional<std::array<int64_t, 3>>
liEu(int64_t a, int64_t b, int64_t c) {
    auto [g, x, y] = exgcd(a, b);
    if (c % g != 0) return {};
    int64_t k = c / g;
    x *= k;
    y *= k;
    // smallest positive x:
    b /= g;
    x = (x % b + b) % b;
    y = (c - a * x) / b;
    return std::array{x, y, g};
}
