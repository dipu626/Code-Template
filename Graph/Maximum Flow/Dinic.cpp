/*
  Algorithm  : Dinic algorithm for finding maximum flow in a directed/undiredted graph
  Complexity : O(V * V * E)
  
  Test : https://toph.co/p/ghosh-vs-datta
*/

template <typename T>
struct Dinic {
      int n;
      vector < vector <int> > graph;
      vector < vector <T> > cap;
      vector < vector <T> > flow;
      vector <int> level;
      vector <int> ptr;

      void init(int tnode) {
            n = tnode;
            graph.clear();          graph.resize(tnode + 1);
            cap.clear();            cap.resize(tnode + 1, vector <T> (tnode + 1));
            flow.clear();           flow.resize(tnode + 1, vector <T> (tnode + 1));
            level.clear();          level.resize(tnode + 1);
            ptr.clear();            ptr.resize(tnode + 1);
      }
      void addEdge(int u, int v, T w) {
            cap[u][v] = w;
            flow[u][v] = 0;
//            cap[v][u] = w; // for undirected graph
//            flow[v][u] = 0;
            graph[u].push_back(v);
            graph[v].push_back(u);
      }
      void updateEdge(int u, int v, T w) {
            cap[u][v] = w;
            flow[u][v] = 0;
//            cap[v][u] = w; // for undirected graph
//            flow[v][u] = 0;
      }
      bool bfs(int src, int sink) {
            fill(level.begin(), level.end(), -1);
            queue <int> pq;
            pq.push(src);
            level[src] = 0;
            while (pq.size()) {
                  int u = pq.front(); pq.pop();
                  for (int v : graph[u]) {
                        if (level[v] != -1 or flow[u][v] >= cap[u][v]) {
                              continue;
                        }
                        level[v] = level[u] + 1;
                        pq.push(v);
                  }
            }
            return level[sink] != -1;
      }
      T dfs(int u, T minCap, int sink) {
            if (u == sink) {
                  return minCap;
            }
            for (int &i = ptr[u]; i < int(graph[u].size()); i++) {
                  int v = graph[u][i];
                  if (level[v] == level[u] + 1 and flow[u][v] < cap[u][v]) {
                        T minFlow = dfs(v, min(minCap, cap[u][v] - flow[u][v]), sink);
                        if (minFlow > 0) {
                              flow[u][v] += minFlow;
                              flow[v][u] -= minFlow;
                              return minFlow;
                        }
                  }
            }
            return 0;
      }
      T maxflow(int src, int sink) {
            T ans = 0;
            while (bfs(src, sink)) {
                  fill(ptr.begin(), ptr.end(), 0);
                  while (T bottleneck = dfs(src, numeric_limits <T> :: max(), sink)) {
                        ans += bottleneck;
                  }
            }
            return ans;
      }
};

void Task() {
      int n, m;
      cin >> n >> m;
      Dinic <long long> PMG; PMG.init(n);
      Dinic <long long> TNT; TNT.init(n);
      vector < vector <long long> > initCap(n + 1, vector <long long> (n + 1));
      for (int e = 1; e <= m; e++) {
            int u, v;
            long long w;
            cin >> u >> v >> w;
            ++u, ++v;
            initCap[u][v] = w;
            PMG.addEdge(u, v, w);
            TNT.addEdge(u, v, w);
      }
      int q;
      cin >> q;
      vector < pair <int, int> > queries(q);
      for (auto &x : queries) {
            cin >> x.first >> x.second;
            ++x.first, ++x.second;
            PMG.updateEdge(x.first, x.second, 0);
            TNT.updateEdge(x.first, x.second, 0);
      }
      int pmg = 1;
      int tnt = n;
      long long pmg_tnt = 0;
      long long tnt_pmg = 0;
      vector <string> ans(q);
      for (int i = q - 1; i >= 0; i--) {
            pmg_tnt += PMG.maxflow(pmg, tnt);
            tnt_pmg += TNT.maxflow(tnt, pmg);
            if (pmg_tnt > tnt_pmg) {
                  ans[i] = "PMG";
            }
            else if (tnt_pmg > pmg_tnt) {
                  ans[i] = "TNT";
            }
            else if (tnt_pmg == 0 and tnt_pmg == 0) {
                  ans[i] = "Datta wins";
            }
            else if (tnt_pmg > 0 and tnt_pmg == pmg_tnt) {
                  ans[i] = "Ghosh wins";
            }
            int u = queries[i].first;
            int v = queries[i].second;
            PMG.updateEdge(u, v, initCap[u][v]);
            TNT.updateEdge(u, v, initCap[u][v]);
      }
      for (int i = 0; i < q; i++) {
            cout << ans[i] << '\n';
      }
}
