#include <vector>
namespace Sieve {
    vector<int> primes;
    vector<int> mn_factor;
    void get_primes(int N) {
        mn_factor.resize(N+1);
        for (int i = 2; i <= N; ++i) {
            if (mn_factor[i]==0) {
                primes.push_back(i);
                mn_factor[i]=i;
            }
            for (auto p : primes){
                if ((long long)i * p > N) break;
                mn_factor[i * p] = p;
                if (i % p == 0) break; 
            }
        }
    }
    bool is_prime(int n) {
        return mn_factor[n]==0;
    }
    vector<pair<int, int>> factor(int n) {
        vector<pair<int, int>> factors;
        while (n > 1) {
            int fac=mn_factor[n], cnt=0;
            while (n%fac==0) {
                cnt++;
                n/=fac;
            }
            factors.emplace_back(fac, cnt);
        }
        return factors;
    };
    vector<int> phi;
    void get_euler(int n) {
        phi.resize(n+1);
        phi[1] = 1;
        for (int i = 2; i <= n; i++) {
            if (phi[i]) continue;
            for (int j = i; j <= n; j += i) {
                if (!phi[j]) phi[j] = j;
                phi[j] = phi[j] / i * (i - 1);
            }
        }
    }
}
using namespace Sieve;
