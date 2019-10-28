//Euler sieve
int pri[MAXN],vis[MAXN],cnt=-1;
void init() {
    for (int i = 2; i < MAXN; ++i) {
        if (!vis[i]) pri[++cnt] = i;
        for (int j = 0; j <= cnt; ++j) {
            if (1ll * i * pri[j] >= MAXN) break;
            vis[i * pri[j]] = 1;
            if (i % pri[j]==0) break; 
        }
    }
}