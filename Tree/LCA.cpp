vector < vector <int> > graph;
int depth[maxn];
int father[maxn][logn];

void dfs(int u = 1, int p = -1, int lvl = 1) {
      for (int i = 1; i < logn; i++) {
            father[u][i] = father[ father[u][i - 1] ][i - 1];
      }
      depth[u] = lvl;
      for (int v : graph[u]) {
            if (v == p) continue;
            father[v][0] = u;
            dfs(v, u, lvl + 1);
      }
}

int find_lca(int u, int v) {
      if (depth[u] < depth[v]) {
            swap(u, v);
      }
      for (int i = logn - 1; i >= 0; i--) {
            if (depth[ father[u][i] ] >= depth[v]) {
                  u = father[u][i];
            }
      }
      if (u == v) {
            return u;
      }
      for (int i = logn - 1; i >= 0; i--) {
            if (father[u][i] != father[v][i]) {
                  u = father[u][i];
                  v = father[v][i];
            }
      }
      return father[u][0];
}

int kth_par(int u, int k) {
      for (int i = logn - 1; i >= 0; i--) {
            if ((1 << i) <= k) {
                  u = father[u][i];
                  k -= (1 << i);
            }
      }
      return u;
}
