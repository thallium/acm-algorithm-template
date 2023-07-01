#pragma once

#include "misc/modint.hpp"
#include <chrono>
#include <random>
#include <string>
#include <vector>

namespace Hashing {
constexpr uint64_t mod = 1'000'000'000'000'000'003ULL;
using hash_t = ModInt<int64_t, mod>;

const hash_t base = std::mt19937_64(std::chrono::steady_clock::now().time_since_epoch().count())() % mod;
static std::vector<hash_t> pow{1};

static void expand_pow(size_t sz) {
    if (pow.size() - 1 >= sz) {
        return;
    }
    auto old_size = pow.size();
    pow.resize(sz + 1);
    for (auto i = old_size; i <= sz; i++) {
        pow[i] = pow[i - 1] * base;
    }
}

struct HashResult {
    HashResult() {}
    HashResult(hash_t _h, size_t _size) : h(_h), len(_size) {}
    HashResult(const std::string& s) {
        for (auto c : s) {
            *this += c;
        }
    }

    HashResult& operator+=(const HashResult &rhs) {
        h = h * pow[rhs.len] + rhs.h;
        len += rhs.len;
        return *this;
    }

    HashResult& operator+=(char ch) {
        h = h * base + ch;
        len += 1;
        return *this;
    }

    friend HashResult operator +(HashResult lhs, HashResult rhs) {
        return lhs += rhs;
    }

    bool operator==(HashResult rhs) const {
        return len == rhs.len && h == rhs.h;
    }

    size_t size() const {
        return len;
    }

    uint64_t hash() const {
        return h.val;
    }
private:
    hash_t h = 0;
    size_t len = 0;
};

struct HashStr {
    HashStr() : pref(1) {}
    HashStr(const std::string& s) : pref(std::size(s) + 1) {
        const auto sz = std::size(s);
        expand_pow(sz);
        for (size_t i = 0; i < sz; i++) {
            pref[i + 1] = pref[i] * base + s[i];
        }
    }

    void push_back(char c) {
        expand_pow(pref.size());
        pref.push_back(pref.back() * base + c);
    }

    void operator+(char c) {
        push_back(c);
    }

    HashResult sub_hash(size_t pos, size_t n) const {
        assert(pos + n < std::size(pref));
        return {pref[pos + n] - pref[pos] * pow[n], n};
    }

    HashResult hash_result() const {
        return {pref.back(), pref.size() - 1};
    }

    uint64_t hash() const {
        return pref.back().val;
    }

    size_t size() const {
        return pref.size() - 1;
    }

// private:
    std::vector<hash_t> pref;
};

struct HashStrView {
    HashStrView(const HashStr &str) : s(str), _pos(0), _n(str.size()) {}
    HashStrView(const HashStr &str, size_t pos, size_t n) : s(str), _pos(pos), _n(n) {}

    HashResult sub_hash(size_t pos, size_t n) const {
        return s.sub_hash(_pos + pos, n);
    }

    HashResult hash_result() const {
        return sub_hash(0, _n);
    }

    HashStrView sub_str(size_t pos, size_t n) {
        return {s, _pos + pos, n};
    }

    uint64_t hash() const {
        return hash_result().hash();
    }

    bool operator==(const HashStrView& rhs) const {
        return hash_result() == rhs.hash_result();
    }
private:
    const HashStr &s;
    size_t _pos, _n;
};
} // namespace Hashing

using Hashing::HashResult;
using Hashing::HashStr;
using Hashing::HashStrView;
