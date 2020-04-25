struct Node {
      int v, e;
      Node(int v = 0, int e = 0)
            : v(v), e(e) {}
};

struct BTree {
      vector < vector <Node> > graph;
      vector < vector <int> > Tree;
      vector <bool> isBridge;
      vector <bool> vis;
      vector <int> dis;
      vector <int> low;
      int dfsTime;
      int compo;
      vector <int> compo_num;
      vector <int> compo_sze;
      vector <bool> used;

      void init(int nodes, int edges) {
            graph.clear(); graph.resize(nodes + 1);
            Tree.clear(); Tree.resize(nodes + 1);
            isBridge.clear(); isBridge.resize(edges + 1);
            vis.clear(); vis.resize(nodes + 1);
            dis.clear(); dis.resize(nodes + 1);
            low.clear(); low.resize(nodes + 1);
            dfsTime = 0;
            compo = 1;
            compo_num.clear(); compo_num.resize(nodes + 1);
            compo_sze.clear(); compo_sze.resize(nodes + 1);
            used.clear(); used.resize(nodes + 1);
      }
      void add_edge(int u, int v, int e) {
            graph[u].emplace_back(v, e);
            graph[v].emplace_back(u, e);
      }
      void find_bridge(int u = 1, int p = -1) {
            vis[u] = 1;
            dis[u] = low[u] = ++dfsTime;
            for (Node it : graph[u]) {
                  int v = it.v;
                  int e = it.e;
                  if (v == p) continue;
                  if (vis[v] == 0) {
                        find_bridge(v, u);
                        low[u] = min(low[u], low[v]);
                        if (dis[u] < low[v]) {
                              isBridge[e] = 1;
                        }
                  }
                  else {
                        low[u] = min(low[u], dis[v]);
                  }
            }
      }
      void dfs(int src) {
            used[src] = 1;
            int cur_compo = compo;
            compo_num[src] = cur_compo;
            compo_sze[cur_compo]++;
            queue <int> pq;
            pq.emplace(src);
            while (pq.size()) {
                  int u = pq.front(); pq.pop();
                  for (Node it : graph[u]) {
                        int v = it.v;
                        int e = it.e;
                        if (used[v]) continue;
                        if (isBridge[e]) {
                              compo++;
                              Tree[cur_compo].emplace_back(compo);
                              Tree[compo].emplace_back(cur_compo);
                              dfs(v);
                        }
                        else {
                              pq.emplace(v);
                              used[v] = 1;
                              compo_num[v] = cur_compo;
                              compo_sze[cur_compo]++;
                        }
                  }
            }
      }
      void build(int root = 1) {
            find_bridge(root);
            dfs(root);
      }
};
