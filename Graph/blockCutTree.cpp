struct BCTree {
      vector < vector <int> > graph;
      vector < vector <int> > Tree;
      vector <bool> vis;
      vector <int> dis;
      vector <int> low;
      int dfsTime;
      int tot;
      vector <int> bcc;
      stack <int> st;

      void init(int nodes) {
            graph.clear(); graph.resize(nodes + 1);
            Tree.clear(); Tree.resize(nodes + 1);
            vis.clear(); vis.resize(nodes + 1);
            dis.clear(); dis.resize(nodes + 1);
            low.clear(); low.resize(nodes + 1);
            dfsTime = 0;
            tot = 0;
            bcc.clear(); bcc.resize(nodes + 1);
            while (st.size()) {
                  st.pop();
            }
      }
      void add_edge(int u, int v) {
            graph[u].push_back(v);
            graph[v].push_back(u);
      }
      void add_edge1(int u, int v) {
            Tree[u].push_back(v);
            Tree[v].push_back(u);
      }
      void find_bcc(int u, int p = -1) {
            vis[u] = 1;
            dis[u] = low[u] = ++dfsTime;
            st.push(u);
            for (int v : graph[u]) {
                  if (v == p) continue;
                  if (vis[v] == 0) {
                        find_bcc(v, u);
                        low[u] = min(low[u], low[v]);
                        if (dis[u] <= low[v]) {
                              tot++;
                              int h;
                              do {
                                    h = st.top(); st.pop();
                                    bcc[h] = tot;
                                    add_edge1(h, tot);
                              } while (h != v);
                              add_edge1(u, tot);
                        }
                  }
                  else {
                        low[u] = min(low[u], dis[v]);
                  }
            }
      }
};
