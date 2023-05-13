#pragma once
#include <cmath>

template<typename T>
struct Point {
    T x, y;
    Point(T x = 0, T y = 0) : x(x), y(y) {}

    Point &operator+=(const Point &p) {
        x += p.x, y += p.y;
        return *this;
    }
    Point &operator-=(const Point &p) {
        x -= p.x, y -= p.y;
        return *this;
    }
    Point &operator*=(const T &v) {
        x *= v, y *= v;
        return *this;
    }
    friend Point operator-(const Point &p) {
        return Point(-p.x, -p.y);
    }
    friend Point operator+(Point lhs, const Point &rhs) {
        return lhs += rhs;
    }
    friend Point operator-(Point lhs, const Point &rhs) {
        return lhs -= rhs;
    }
    friend Point operator*(Point lhs, const T &rhs) {
        return lhs *= rhs;
    }

    T dist2() const { return x * x + y * y; }
    auto dist() const { return std::sqrt(dist2()); }

    friend T dot(const Point &a, const Point &b) {
        return a.x * b.x + a.y * b.y;
    }
    friend T cross(const Point &a, const Point &b) {
        return a.x * b.y - a.y * b.x;
    }
    friend T cross3(const Point& a, const Point& b, const Point& c) { return cross(b-a, c-a); }
};
