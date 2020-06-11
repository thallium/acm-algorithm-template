int vis[N];
vector<int> primes;
void init() {
    for (int i = 2; i < N; ++i) {
        if (!vis[i]) primes.push_back(i);
        for(auto p:primes){
            if (1ll * i * p >= N) break;
            vis[i * p] = 1;
            if (i % p==0) break; 
        }
    }
}
