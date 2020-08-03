/*
  Algorithm  : Squart Root Decompostion on Tree
  Problem    : E. Xenia and Tree
  OJ         : https://codeforces.com/contest/342/problem/E
  
  Complexity : O(q * sqrt(n) * logn)
  
  Problem : Xenia needs to learn how to quickly execute queries of two types.
            1. paint a specified blue node in red;
            2. calculate which red node is the closest to the given one and print the shortest distance to the closest red node.
*/

vector < vector <int> > graph;
int depth[maxn];
int father[maxn][logn];

void dfs(int u = 1, int p = 0) {
      depth[u] = depth[p] + 1;
      father[u][0] = p;
      for (int i = 1; i < logn; i++) {
            father[u][i] = father[ father[u][i - 1] ][i - 1];
      }
      for (int v : graph[u]) {
            if (v == p) {
                  continue;
            }
            dfs(v, u);
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

int dist[maxn];

void bfs(vector <int> &block_reds) {
      queue <int> pq;
      for (int x : block_reds) {
            pq.push(x);
            dist[x] = 0;
      }
      while (pq.size()) {
            int u = pq.front();
            pq.pop();
            for (int v : graph[u]) {
                  if (dist[v] > dist[u] + 1) {
                        dist[v] = dist[u] + 1;
                        pq.push(v);
                  }
            }
      }
}

void solve() {
      int n, q;
      cin >> n >> q;
      graph.clear();
      graph.resize(n + 1);
      for (int e = 1; e < n; e++) {
            int u, v;
            cin >> u >> v;
            graph[u].push_back(v);
            graph[v].push_back(u);
      }
      vector < pair <int, int> > queries(q);
      for (int i = 0; i < q; i++) {
            cin >> queries[i].first >> queries[i].second;
      }
      depth[1] = 1;
      dfs();
      for (int i = 1; i <= n; i++) {
            dist[i] = 1e9 + 9;
      }
      vector <int> block_reds;
      block_reds.push_back(1);
      bfs(block_reds);
      for (int i = 0; i < q; i += block) {
            block_reds.clear();
            for (int j = 0; j < block; j++) {
                  int k = i + j;
                  if (k >= q) {
                        break;
                  }
                  if (queries[k].first == 1) {
                        block_reds.push_back(queries[k].second);
                  }
                  else {
                        int v = queries[k].second;
                        int min_dist = dist[v];
                        for (int u : block_reds) {
                              int lca = find_lca(u, v);
                              int d = depth[u] + depth[v] - 2 * depth[lca];
                              min_dist = min(min_dist, d);
                        }
                        cout << min_dist << endl;
                  }
            }
            bfs(block_reds);
      }
}
