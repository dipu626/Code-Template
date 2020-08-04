/*
  Algorithm : System of Difference Constraints
  Tutorial  : https://reponroy.wordpress.com/2016/06/27/system-of-difference-constraints/
  
  Statement : You are given a directed graph consisting of n vertices and m edges (each edge is directed, so it can be traversed in only one direction). 
              You need to assign a value Pi to each vertex i from 1 to n so that for each edge u→v having weight w, Pv-Pu ≤ w is satisfied.
              
  Test      : https://toph.co/p/playing-on-a-directed-graph
*/

struct SystemOfDifferenceConstraints {
      struct Node {
            int v;
            long long w;
            Node(int v = 0, long long w = 0)
                  : v(v), w(w) {}
      };

      int n;
      vector < vector <Node> > graph;
      vector <long long> dist;
      vector <int> occ;
      vector <int> inQueue;

      void init(int tnode) {
            n = tnode;
            graph.clear();          graph.resize(tnode + 1);
            dist.clear();           dist.resize(tnode + 1);
            occ.clear();            occ.resize(tnode + 1);
            inQueue.clear();        inQueue.resize(tnode + 1);
      }
      void addEdge(int u, int v, long long w) {
            graph[u].push_back(Node(v, w));
      }
      bool spfa(int src) {
            for (int i = 0; i <= n; i++) {
                  dist[i] = INF;
                  inQueue[i] = 0;
                  occ[i] = 0;
            }
            queue <int> pq;
            pq.push(src);
            dist[src] = 0;
            inQueue[src] = 1;
            occ[src] = 1;
            while (pq.size()) {
                  int u = pq.front(); pq.pop();
                  inQueue[u] = 0;
                  if (occ[u] > n) {
                        return false;
                  }
                  for (Node to : graph[u]) {
                        int v = to.v;
                        long long w = to.w;
                        if (dist[v] > dist[u] + w) {
                              occ[v]++;
                              dist[v] = dist[u] + w;
                              if (inQueue[v] == 0) {
                                    inQueue[v] = 1;
                                    pq.push(v);
                              }
                        }
                  }
            }
            return true;
      }
      bool solve() {
            int src = 0;
            for (int i = 1; i <= n; i++) {
                  graph[src].push_back(Node(i, 0));
            }
            return spfa(src);
      }
};
