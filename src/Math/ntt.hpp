#include <vector>
#include "misc/util.hpp"

using ll = int64_t;
constexpr int P = 998244353;

static int power(int a, int b) {
    int res = 1;
    for (; b; b >>= 1, a = (ll)a * a % P)
        if (b & 1)
            res = (ll)res * a % P;
    return res;
}

static void dft(std::vector<int> &a) {
    static std::vector<int> rev, roots{0, 1};
    int n = a.size();
    if (int(rev.size()) != n) {
        int k = __builtin_ctz(n) - 1;
        rev.resize(n);
        for (int i = 0; i < n; ++i)
            rev[i] = rev[i >> 1] >> 1 | (i & 1) << k;
    }
    for (int i = 0; i < n; ++i)
        if (rev[i] < i)
            std::swap(a[i], a[rev[i]]);
    if (int(roots.size()) < n) {
        int k = __builtin_ctz(roots.size());
        roots.resize(n);
        while ((1 << k) < n) {
            int e = power(3, (P - 1) >> (k + 1));
            for (int i = 1 << (k - 1); i < (1 << k); ++i) {
                roots[2 * i] = roots[i];
                roots[2 * i + 1] = (ll)roots[i] * e % P;
            }
            ++k;
        }
    }
    for (int k = 1; k < n; k *= 2) {
        for (int i = 0; i < n; i += 2 * k) {
            for (int j = 0; j < k; ++j) {
                int u = a[i + j];
                int v = (ll)a[i + j + k] * roots[k + j] % P;
                int x = u + v;
                if (x >= P)
                    x -= P;
                a[i + j] = x;
                x = u - v;
                if (x < 0)
                    x += P;
                a[i + j + k] = x;
            }
        }
    }
}

static void idft(std::vector<int> &a) {
    int n = a.size();
    std::reverse(a.begin() + 1, a.end());
    dft(a);
    int inv = power(n, P - 2);
    for (int i = 0; i < n; ++i)
        a[i] = (ll)a[i] * inv % P;
}

// calculates the convolution of a and b
static
std::vector<int> convolve(const std::vector<int> &a, const std::vector<int> &b) {
    auto fa{a}, fb{b};
    int n = 1 << (lg(size(a) + size(b) - 1) + 1);
    fa.resize(n);
    fb.resize(n);

    dft(fa);
    dft(fb);
    for (int i = 0; i < n; i++)
        fa[i] = (ll)fa[i] * fb[i] % P;
    idft(fa);

    return fa;
}
