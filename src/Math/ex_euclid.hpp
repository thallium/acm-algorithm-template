#pragma once

#include <array>
#include <cstdint>
#include <optional>

// Returns {x, y, g} which is a solution to a * x + b * y = g = gcd(a, b)
inline std::array<int64_t, 3> exgcd(int64_t a, int64_t b) {
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
static std::optional<std::array<int64_t, 3>>
liEu(int64_t a, int64_t b, int64_t c) {
    auto [x, y, g] = exgcd(a, b);
    if (c % g != 0) return {};
    int64_t k = c / g;
    x *= k;
    y *= k;
    // smallest positive x:
    int64_t t = b / g;
    x = (x % t + t) % t;
    y = (c - a * x) / b;
    return std::array{x, y, g};
}
