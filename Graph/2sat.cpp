/*
  Problem  : 2-Satisfiability
  Tutorial : https://www.geeksforgeeks.org/2-satisfiability-2-sat-problem/
             https://cp-algorithms.com/graph/2SAT.html
             https://codeforces.com/blog/entry/16205
             
  Algorithm : (x and y)   = x' -> y            y' -> x
              (x and y')  = x' -> y'           y -> x
              (x' and y)  = x -> y             y' -> x'
              (x' and y') = x -> y'            y -> x'
              
  Test : https://codeforces.com/contest/228/problem/E
*/

vector < vector <int> > graph;
vector < vector <int> > rgraph;
int dfsTime;
int finishTime[maxn];
int rdfsTime;
int rfinishTime[maxn];
bool vis[maxn];
bool vis_scc[maxn];
int scc_no[maxn];

void dfs(int u) {
      vis[u] = 1;
      for (int v : graph[u]) {
            if (vis[v]) {
                  continue;
            }
            dfs(v);
      }
      finishTime[u] = ++dfsTime;
}

void dfs_scc(int u, int compo) {
      vis_scc[u] = 1;
      scc_no[u] = compo;
      for (int v : rgraph[u])
      {
            if (vis_scc[v]) {
                  continue;
            }
            dfs_scc(v, compo);
      }
      rfinishTime[u] = ++rdfsTime;
}

void solve() {
      int city, road;
      cin >> city >> road;
      graph.clear(); graph.resize(2 * city + 1);
      rgraph.clear(); rgraph.resize(2 * city + 1);
      for (int r = 1; r <= road; r++)
      {
            int u, v, status;
            cin >> u >> v >> status;
            int x = u;
            int y = v;
            int xprime = city + u;
            int yprime = city + v;
            if (status == 0) {        // (x and y) or (x' and y')
                  graph[xprime].emplace_back(y);
                  graph[yprime].emplace_back(x);
                  rgraph[y].emplace_back(xprime);
                  rgraph[x].emplace_back(yprime);

                  graph[x].emplace_back(yprime);
                  graph[y].emplace_back(xprime);
                  rgraph[yprime].emplace_back(x);
                  rgraph[xprime].emplace_back(y);
            }
            else {                   // (x and y') or (x' and y)
                  graph[xprime].emplace_back(yprime);
                  graph[y].emplace_back(x);
                  rgraph[yprime].emplace_back(xprime);
                  rgraph[x].emplace_back(y);

                  graph[x].emplace_back(y);
                  graph[yprime].emplace_back(xprime);
                  rgraph[y].emplace_back(x);
                  rgraph[xprime].emplace_back(yprime);
            }
      }
      for (int i = 1; i <= 2 * city; i++) {
            if (vis[i] == 0) {
                  dfs(i);
            }
      }
      vector <int> order(2 * city + 1);
      iota(all(order), 0);
      sort(order.begin() + 1, order.end(), [&](int i, int j) { return finishTime[i] > finishTime[j]; } );
      debug(order);
      int compo = 0;
      for (int i = 1; i <= 2 * city; i++) {
            int u = order[i];
            if (vis_scc[u] == 0) {
                  dfs_scc(u, ++compo);
            }
      }
      vector <int> True;
      for (int i = 1; i <= city; i++) {
            if (scc_no[i] == scc_no[city + i]) {
                  puts("Impossible");
                  exit(0);
            }
            if (rfinishTime[i] > rfinishTime[city + i]) {
                  True.push_back(i);
            }
      }
      cout << True.size() << endl;
      for (int x : True) {
            cout << x << " ";
      }
      cout << endl;
}
