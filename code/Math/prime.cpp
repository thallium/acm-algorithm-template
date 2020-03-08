//cnt is one greater than the number of primes
// when traversing the pri array, use forn(i,cnt)
int pri[N],vis[N],cnt=0;
void init() {
    for (int i = 2; i < N; ++i) {
        if (!vis[i]) pri[cnt++] = i;
        for (int j = 0; j < cnt; ++j) {
            if (1ll * i * pri[j] >= N) break;
            vis[i * pri[j]] = 1;
            if (i % pri[j]==0) break; 
        }
    }
}
