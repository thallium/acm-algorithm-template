namespace Factorial {
    vector<mint> fac, invfac;
    void init(int n) {
        fac.resize(n+1);
        invfac.resize(n+1);
        fac[0]=1;
        for (int i=1; i<=n; i++) fac[i]=fac[i-1]*i;
        invfac[n]=fac[n].inv();
        for (int i=n-1; i>=0; i--) invfac[i]=invfac[i+1]*(i+1);
    }

    mint C(int n, int m) { // n choose m
        return fac[n]*invfac[n-m]*invfac[m];
    }

    mint P(int n, int m) { // n choose m with permutation
        return fac[n]*invfac[n-m];
    }
}
using namespace Factorial;
