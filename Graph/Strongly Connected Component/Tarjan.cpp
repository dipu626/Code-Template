/*
  Algorithm  : Tarjan algorithm for finding strongly connected component in a directed graph
  Complexity : O(n + m)
  
  Test : UVA 10510 - Cactus
*/

struct Tarjan {
      int n;
      vector < vector <int> > graph;
      vector < vector <int> > sccNodes;
      vector <int> father;
      vector <int> cyclePart;
      vector <int> sccno;
      vector <int> discovery;
      vector <int> low;
      vector <int> stackMember;
      int dfsTime;
      int nscc;
      stack <int> st;

      void init(int tnode) {
            n = tnode;
            graph.clear();          graph.resize(tnode + 1);
            sccNodes.clear();       sccNodes.resize(tnode + 1);
            father.clear();         father.resize(tnode + 1);
            cyclePart.clear();      cyclePart.resize(tnode + 1);
            sccno.clear();          sccno.resize(tnode + 1);
            discovery.clear();      discovery.resize(tnode + 1);
            low.clear();            low.resize(tnode + 1);
            stackMember.clear();    stackMember.resize(tnode + 1);
            dfsTime = 0;
            nscc = 0;
            while (st.size())       st.pop();
      }
      void addEdge(int u, int v) {
            if (u == v) {
                  return;
            }
            graph[u].push_back(v);
      }
      void printCycle(int v, int u) {
            while (father[u] != v) {
                  cyclePart[u]++;
                  if (cyclePart[u] > 1) { // edge u-father[u] is part of more than 1 scc
                        break;
                  }
                  u = father[u];
            }
      }
      void dfs(int u) {
            discovery[u] = low[u] = ++dfsTime;
            st.push(u);
            stackMember[u] = true;
            for (int v : graph[u]) {
                  if (discovery[v] == 0) {
                        father[v] = u;
                        dfs(v);
                        low[u] = min(low[u], low[v]);
                  }
                  else if (stackMember[v] == true) {
                        low[u] = min(low[u], discovery[v]);
                        printCycle(v, u);
                  }
            }
            if (discovery[u] == low[u]) { // Found a scc
                  nscc++;
                  while (true) {
                        int node = st.top(); st.pop();
                        sccno[node] = nscc;
                        sccNodes[nscc].push_back(node);
                        stackMember[node] = false; // update it to 0 to not enter a cross edge
                        if (node == u) {
                              break;
                        }
                  }
            }
      }
      void tarjan() {
            for (int i = 1; i <= n; i++) {
                  if (discovery[i] == 0) {
                        dfs(i);
                  }
            }
      }
};

signed main()
{
      int tc;
      cin >> tc;
      while (tc--) {
            int n, m;
            cin >> n >> m;
            Tarjan tarjan;
            tarjan.init(n);
            vector <int> selfLoops;
            for (int e = 1; e <= m; e++) {
                  int u, v;
                  cin >> u >> v;
                  tarjan.addEdge(u + 1, v + 1);
            }
            tarjan.tarjan();
            bool cactus = (tarjan.nscc == 1);
            for (int i = 0; i <= n; i++) {
                  if (tarjan.cyclePart[i] > 1) {
                        cactus = false;
                  }
            }
            cout << (cactus ? "YES" : "NO") << endl;
      }
}
