/**
      Eulerian path    : Eulerian Path is a path in graph that visits every edge exactly once.
      Eulerian circuit : Eulerian Circuit is an Eulerian Path which starts and ends on the same vertex.

      Undirected graph: circuit (or edge disjoint cycles) exists iff all nodes are of even degree.
      Undirected graph: path exists iff number of odd degree nodes is zero or two.

      Directed graph: circuit (or edge disjoint directed cycles) exists iff each node satisfies
      in_degree = out_degree and the graph is strongly connected.
      Directed graph: path exists iff at most one vertex has in_degree - out_degree = 1
      and at most one vertex has out_degree - in_degree = 1 and all other vertices have
      in_degree = out_degree, and graph is weakly connected.
**/

/**
      use this source code for undirected and directed graph.
**/

vector < vector <int> > graph;
vector <int> circuit;
int n;
int m;
vector <int> deg;
vector <bool> bad;
vector <int> U;
vector <int> V;

void hierholzer(int src) {
      if (deg[src] == 0) {
            return;
      }
      vector <int> path;
      path.push_back(src);
      int att = src;
      while (path.size()) {
            if (deg[att]) {
                  path.push_back(att);
                  while (bad[graph[att].back()]) {
                        graph[att].pop_back();
                  }
                  int e = graph[att].back();
                  int nxt = U[e] ^ att ^ V[e];
                  bad[e] = 1;
                  --deg[att];
                  --deg[nxt];
                  att = nxt;
            }
            else {
                  circuit.push_back(att);
                  att = path.back();
                  path.pop_back();
            }
      }
      reverse(circuit.begin(), circuit.end());
}

signed main()
{
      cin >> n >> m;
      graph.resize(n + 1);
      deg.resize(n + 1);
      bad.resize(m + 1);
      U.resize(m + 1);
      V.resize(m + 1);
      for (int e = 1; e <= m; e++) {
            cin >> U[e] >> V[e];
            graph[ U[e] ].eb(e);
            graph[ V[e] ].eb(e);
            deg[ U[e] ]++;
            deg[ V[e] ]++;
      }
      hierholzer(1);
      for (int x : circuit) {
            cout << x << " ";
      }
      cout << endl;
}
