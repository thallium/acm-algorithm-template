#include<bits/stdc++.h>
using namespace std;
using u64 = uint64_t;
using u128 = __uint128_t;
using ll = long long;
 
u64 binPow(u64 a, u64 b, u64 mod){
    if(b == 0) return 1;
    if(b&1) return (u128)a * binPow(a, b^1, mod) % mod;
    return binPow((u128)a * a % mod, b>>1, mod);
}
 
bool checkComp(u64 n, u64 a, u64 d, int s){
    u64 x = binPow(a, d, n);
    if(x == 1 || x == n-1) return false;
    for (int r=1; r<s; r++) {
        x = (u128)x * x % n;
        if(x == n-1) return false;
    }
    return true;
}
 
bool RabinMiller(u64 n){
    if(n < 2) return false;
    int r = 0;
    u64 d = n-1;
    while(!(d & 1))
        d >>= 1, r++;
    for(int a : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37}){
        if(n == a) return true;
        if(checkComp(n, a, d, r)) return false;
    }
    return true;
}
ll mult(ll a, ll b, ll mod){
    return (__int128)a * b % mod;
}
ll f(ll x, ll c, ll mod){
    return (mult(x, x, mod) + c) % mod;
}
ll rho(ll n){ // Works in O(n^(1/4) * log(n))
    ll x = 2, y = 2, g = 1;
    ll c = rand() % n + 1;
    while(g == 1){
        x = f(x, c, n);
        y = f(y, c, n);
        y = f(y, c, n);
        g = gcd(abs(x - y), n);
    }
    return g==n ? rho(n) : g;
}
map <ll, ll> fact;
void factRho(ll n){
    if(n == 1) return;
    if(RabinMiller(n)){
        fact[n]++;
        return;
    }
    ll factor = rho(n);
    factRho(factor);
    factRho(n/factor);
}
