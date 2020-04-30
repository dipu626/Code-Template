static const int maxn = 2e5 + 5;
static const int logn = 19;

vector < vector <int> > graph;
int depth[maxn];
int father[maxn][logn];
int in[maxn];
int out[maxn];
int dfsTime;

void dfs(int u = 1, int p = -1, int lvl = 1) {
      in[u] = ++dfsTime;
      for (int i = 1; i < logn; i++) {
            father[u][i] = father[ father[u][i - 1] ][i - 1];
      }
      depth[u] = lvl;
      for (int v : graph[u]) {
            if (v == p) {
                  continue;
            }
            father[v][0] = u;
            dfs(v, u, lvl + 1);
      }
      out[u] = dfsTime;
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

struct Node {
      int v, w;
      Node(int v = 0, int w = 0)
            : v(v), w(w) {}
};

vector < vector <Node> > vtree;

void add_edge(int u, int v) {
      if (u == v) {
            return;
      }
      int w = abs(depth[u] - depth[v]);
//      cerr << "u=" << u << " v=" << v << " w=" << w << endl;
      vtree[u].emplace_back(v, w);
      vtree[v].emplace_back(u, w);
}

int build(vector <int> &nodes) {
      if (nodes.size() <= 1) {
            return -1;
      }
      sort(nodes.begin(), nodes.end(), [&](int x, int y){ return in[x] < in[y]; });
      int root = find_lca(nodes[0], nodes.back());
//      cerr << "root=" << root << endl;
      vector <int> alive;
      alive.push_back(root);
      for (int v : nodes) {
            int lca = find_lca(alive.back(), v);
            if (alive.back() == lca) {
                  alive.push_back(v);
            }
            else {
                  while (alive.size() > 1) {
                        int x = alive[ alive.size() - 2 ];
                        int y = alive.back();
                        if (depth[x] >= depth[lca]) {
                              add_edge(x, y);
                              alive.pop_back();
                        }
                        else {
                              break;
                        }
                  }
                  if (alive.back() != lca) {
                        add_edge(alive.back(), lca);
                        alive.pop_back();
                        alive.push_back(lca);
                        nodes.push_back(lca);
                  }
                  alive.push_back(v);
            }
      }
      if (find(nodes.begin(), nodes.end(), root) == nodes.end()) {
            nodes.push_back(root);
      }
      for (int i = 1; i < alive.size(); i++) {
            add_edge(alive[i - 1], alive[i]);
      }
      return root;
}

void clean(vector <int> &nodes) {
      for (int x : nodes) {
            vtree[x].clear();
      }
}

signed main()
{
      ios_base::sync_with_stdio(false);
      cin.tie(nullptr);

      #ifndef ONLINE_JUDGE
          freopen("in.txt", "r", stdin);
      #endif // ONLINE_JUDGE

      int n;
      cin >> n;
      graph.resize(n + 1);
      vtree.resize(n + 1);
      for (int e = 1; e < n; e++) {
            int u, v;
            cin >> u >> v;
            graph[u].push_back(v);
            graph[v].push_back(u);
      }
      dfs();
      int m;
      cin >> m;
      vector <int> nodes(m);
      for (int &x : nodes) {
            cin >> x;
      }
      int root = build(nodes);
      clean(nodes);
}
