struct Dominator {
      int n;

      vector < vector <int> > graph;
      vector < vector <int> > rgraph;
      vector < vector <int> > Tree;
      vector < vector <int> > bucket;

      vector <int> arr;
      vector <int> par;
      vector <int> rev;
      vector <int> sdom;
      vector <int> dom;
      vector <int> dsu;
      vector <int> level;

      int dfsTime;

      void init(int tnode) {
            n = tnode;

            graph.clear();          graph.resize(tnode + 1);
            rgraph.clear();         rgraph.resize(tnode + 1);
            Tree.clear();           Tree.resize(tnode + 1);
            bucket.clear();         bucket.resize(tnode + 1);

            arr.clear();            arr.resize(tnode + 1);
            par.clear();            par.resize(tnode + 1);
            rev.clear();            rev.resize(tnode + 1);
            sdom.clear();           sdom.resize(tnode + 1);
            dom.clear();            dom.resize(tnode + 1);
            dsu.clear();            dsu.resize(tnode + 1);
            level.clear();          level.resize(tnode + 1);

            dfsTime = 0;
      }
      // 1 - based directed graph
      void addEdge(int u, int v) {
            graph[u].push_back(v);
      }
      int Find(int u, int x = 0) {
            if (u == dsu[u]) {
                  return x ? -1 : u;
            }
            int v = Find(dsu[u], x+1);
            if (v < 0) {
                  return u;
            }
            if (sdom[ level[ dsu[u] ] ] < sdom[ level[u] ]) {
                  level[u] = level[ dsu[u] ];
            }
            dsu[u] = v;
            return x ? v : level[u];
      }
      void Union(int u, int v) { // Add an edge to u -> v
            dsu[v] = u;
      }
      void dfs(int u) {
            ++dfsTime;
            arr[u] = dfsTime;
            rev[dfsTime] = u;
            level[dfsTime] = dfsTime;
            sdom[dfsTime] = dfsTime;
            dsu[dfsTime] = dfsTime;
            for (int v : graph[u]) {
                  if (!arr[v]) {
                        dfs(v);
                        par[ arr[v] ] = arr[u];
                  }
                  rgraph[ arr[v] ].emplace_back(arr[u]);
            }
      }
      void build(int src) {
            dfs(src);
            int n = dfsTime;
            for (int i = n; i >= 1; i--) {
                  for (int j = 0; j < int(rgraph[i].size()); j++) {
                        sdom[i] = min(sdom[i], sdom[ Find(rgraph[i][j]) ]);
                  }
                  if (i > 1) {
                        bucket[ sdom[i] ].emplace_back(i);
                  }
                  for (int j = 0; j < int(bucket[i].size()); j++) {
                        int w = bucket[i][j];
                        int v = Find(w);
                        if (sdom[v] == sdom[w]) {
                              dom[w] = sdom[w];
                        }
                        else {
                              dom[w] = v;
                        }
                  }
                  if (i > 1) {
                        Union(par[i], i);
                  }
            }
            for (int i = 2; i <= n; i++) {
                  if (dom[i] != sdom[i]) {
                        dom[i] = dom[ dom[i] ];
                  }
                  Tree[ rev[i] ].emplace_back(rev[ dom[i] ]);
                  Tree[ rev[ dom[i] ] ].emplace_back(rev[i]);
            }
      }
};
