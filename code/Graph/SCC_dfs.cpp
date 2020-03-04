void dfs1(int u) {
  vis[u] = true;
  for (int v : G[u])
    if (!vis[v]) dfs1(v);
  order.push_back(u);
}

void dfs2(int u) {
  color[u] = sccCnt;
  for (int v : G2[u])
    if (!color[v]) dfs2(v);
}

void kosaraju() {
  sccCnt = 0;
  for (int i = 1; i <= n; ++i)
    if (!vis[i]) dfs1(i);
  for (int i = n; i >= 1; --i)
    if (!color[order[i]]) {
      ++sccCnt;
      dfs2(s[i])
    }
}