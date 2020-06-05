static const int max_node = 1e3 + 5; // Maximum number of Node
static const int max_edge = 1e5 + 5; // Maximum number of Edge
static const int inf      = 1e9 + 9;

struct Edge {
      int u, v, w;
      Edge(int u = 0, int v = 0, int w = 0)
            : u(u), v(v), w(w) {}
};

vector <Edge> edges;

int directed_mst(int root, int nv, int ne) {
//      root = starting node
//      nv   = number of nodes, starting from 0
//      ne   = number of edges, starting from 0

      vector <int> min_incoming(nv); // minimum weight among all incoming edges
      vector <int> pre(nv);          // parent of node v
      vector <int> cycle_id(nv);     // id of the corresponding cycle
      vector <int> vis(nv);          // used to determine cycle
      vector <Edge> tedges(ne);      // temporary edges, which will be changed during finding mst

      tedges = edges;
      int dmst = 0;
      while (true) {
            for (int i = 0; i < nv; i++) {
                  min_incoming[i] = inf;
                  cycle_id[i] = -1;
                  vis[i] = -1;
            }
            for (int i = 0; i < ne; i++) {
                  int u = tedges[i].u;
                  int v = tedges[i].v;
                  int w = tedges[i].w;
                  if (u != v and w < min_incoming[v]) { // Taking lowest incoming edge
                        min_incoming[v] = w;
                        pre[v] = u;
                  }
            }
            for (int i = 0; i < nv; i++) {
                  if (i == root) {
                        continue;
                  }
                  if (min_incoming[i] == inf) {
                        return -1; // Impossible case
                  }
            }
            min_incoming[root] = 0;
            pre[root] = root; // This need to set up, or can cause infinite loop
            int cnt_node = 0;
            for (int i = 0; i < nv; i++) {
                  dmst += min_incoming[i];
                  if (vis[i] == -1) {
                        int v = i;
                        while (vis[v] == -1) {
                              vis[v] = i;
                              v = pre[v];  // climbing up
                        }
                        if (v == root or vis[v] != i) {
                              continue;
                        }
                        cycle_id[v] = cnt_node; // new cycle, put all the member in same id
                        for (int u = pre[v]; u != v; u = pre[u]) {
                              cycle_id[u] = cnt_node;
                        }
                        cnt_node++;
                  }
            }
            if (cnt_node == 0) {
                  break;
            }
            for (int i = 0; i < nv; i++) {
                  if (cycle_id[i] == -1) {
                        cycle_id[i] = cnt_node++;
                  }
            }
            for (int i = 0; i < ne; i++) {
                  int tmp = tedges[i].v;
                  tedges[i].u = cycle_id[ tedges[i].u ];
                  tedges[i].v = cycle_id[ tedges[i].v ];
                  if (tedges[i].u != tedges[i].v) {
                        tedges[i].w -= min_incoming[tmp];
                  }
            }
            nv = cnt_node;
            root = cycle_id[root];
      }
      return dmst;
}

signed main()
{
      ios_base::sync_with_stdio(false);
      cin.tie(nullptr);
      cout.precision(12);

      #ifndef ONLINE_JUDGE
          freopen("in.txt", "r", stdin);
      #endif // ONLINE_JUDGE

      int tc;
      cin >> tc;
      for (int tcase = 1; tcase <= tc; tcase++) {
            int tnode, tedge;
            cin >> tnode >> tedge;
            edges.clear();
            edges.resize(tedge);
            for (Edge &x : edges) {
                  cin >> x.u >> x.v >> x.w;
            }
            int dmst = directed_mst(0, tnode, tedge);
            cout << "Case #" << tcase << ": ";
            if (dmst == -1) {
                  cout << "Possums!" << endl;
            }
            else {
                  cout << dmst << endl;
            }
      }

      #ifndef ONLINE_JUDGE
            cerr << endl << "Time : " << 1.0 * clock() / CLOCKS_PER_SEC << " s." << endl;
      #endif // ONLINE_JUDGE
}
