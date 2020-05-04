/*
      Heavy Light Decomposition
      Unweighted Tree (Node Cost)
*/

struct HLD {
      int n;
      vector < vector <int> > graph;
      vector < vector <int> > Tree;
      vector <int> sub_size;
      vector <int> nxt;
      vector <int> in;
      vector <int> out;
      int dfsTime;
      vector <ll> cost;
      vector <int> depth;
      vector < vector <int> > father;

      void init(int nodes) {
            n = nodes + 1;
            graph.clear();    graph.resize(n);
            Tree.clear();     Tree.resize(n);
            sub_size.clear(); sub_size.resize(n);
            nxt.clear();      nxt.resize(n);
            in.clear();       in.resize(n);
            out.clear();      out.resize(n);
            dfsTime = 0;
            cost.clear();     cost.resize(n);
            depth.clear();    depth.resize(n);
            father.clear();   father.resize(n, vector <int> (logn));
      }
      void add_cost(int u, ll cst) {
            cost[u] = cst;
      }
      void add_edge(int u, int v) {
            graph[u].emplace_back(v);
            graph[v].emplace_back(u);
      }
      void make_tree(int u, int p) {
            for (int v : graph[u]) {
                  if (v == p) {
                        continue;
                  }
                  Tree[u].push_back(v);
                  make_tree(v, u);
            }
      }
      void dfs(int u, int p, int lvl) {
            depth[u] = lvl;
            father[u][0] = p;
            for (int i = 1; i < logn; i++) {
                  father[u][i] = father[ father[u][i - 1] ][i - 1];
            }
//            sub_size[u] = 1; // don't initialize it
            for (int v : Tree[u]) {
                  dfs(v, u, lvl + 1);
                  sub_size[u] += sub_size[v];
                  if (sub_size[v] > sub_size[ Tree[u][0] ]) {
                        swap(v, Tree[u][0]);
                  }
            }
      }
      void print(int u = 1) {
            for (int v : Tree[u]) {
//                  cerr << __LINE__ << ": " << u << " " << v << endl;
                  print(v);
            }
      }
      void hld(int u) {
            in[u] = ++dfsTime;
            for (int v : Tree[u]) {
                  nxt[v] = v == Tree[u][0] ? nxt[u] : v;
                  hld(v);
            }
            out[u] = dfsTime;
//            cerr << __LINE__ << ": u=" << u << " nxt=" << nxt[u] << endl;
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
      ll query_up(int u, int lca) {
            ll sum = 0;
            while (true) {
                  if (depth[ nxt[u] ] <= depth[lca]) {
                        int l = in[lca];
                        int r = in[u];
                        if (l <= r) {
      //                      sum += query(l, r); // Use necessary data structure
                        }
                        break;
                  }
                  int l = in[ nxt[u] ];
                  int r = in[u];
                  assert(l <= r);
//                  sum += query(l, r); // Use necessary data structure
                  u = father[ nxt[u] ][0];
            }
            return sum;
      }
      ll query_path(int u, int v) {
            int lca = find_lca(u, v);
            ll sum1 = query_up(u, lca);
            ll sum2 = query_up(v, lca);
            ll sum_lca = query_up(lca, lca);
            return sum1 + sum2 - sum_lca;
      }
      ll query_subtree(int u) {
            int l = in[u];
            int r = in[u];
            ll sum = 0; // Use necessary data structure
            return sum;
      }
      void update_up(int u, int lca, ll val) {
            while (true) {
                  if (depth[ nxt[u] ] <= depth[lca]) {
                        int l = in[lca];
                        int r = in[u];
                        if (l <= r) {
      //                      sum += query(l, r); // Use necessary data structure
                        }
                        break;
                  }
                  int l = in[ nxt[u] ];
                  int r = in[u];
                  assert(l <= r);
//                  update(l, r, val); // Use necessary data structure
                  u = father[ nxt[u] ][0];
            }
      }
      void update_path(int u, int v, ll val) {
            int lca = find_lca(u, v);
            update_up(u, lca, val);
            update_up(v, lca, val);
            update_up(lca, lca, -val);
      }
      void update_node(int u, ll val) {
            int l = in[u];
//            update(in[u], val); // Use necessary data structure
      }
      void subtree_update(int u, ll val) {
            int l = in[u];
            int r = out[u];
//            update(l, r, val) // Use necessary data structure
      }
      void build(int root = 1) {
            make_tree(root, 0);
            dfs(root, 0, 1);
            nxt[root] = root;
            hld(root);
            for (int i = 1; i <= n; i++) {
                  int l = in[i];
//                  update(l, l, cost[i]);
            }
      }
};
