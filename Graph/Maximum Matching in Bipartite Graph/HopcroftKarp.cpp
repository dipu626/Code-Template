/**
      Hopcroft-Karp Algorithm for Maximum Matching in Bipartite Graph
      Complexity : O(sqrt(V) x E)
**/

int in_left;    // number of elements in left side
int in_right;   // number of elements in right side
int NILL = 0;
vector < vector <int> > graph;

int pairU[maxn];
int pairV[maxn];
int dist[maxn];
//int match[maxn]; // If we can't divide the graph in two parts, use match[]
                   // http://dipusnotebook.blogspot.com/2019/01/light-oj-1356-prime-independence.html

void init() {
      for (int i = 0; i < maxn; i++) {
            pairU[i] = NILL;
            pairV[i] = NILL;
      }
}

bool bfs() {
      queue <int> pq;
      for (int i = 1; i <= in_left; i++) {
            if (pairU[i] == NILL) {
                  dist[i] = NILL;
                  pq.emplace(i);
            }
            else {
                  dist[i] = INF;
            }
      }
      dist[NILL] = INF;
      while (pq.size()) {
            int u = pq.front(); pq.pop();
            if (u and dist[u] < dist[NILL]) {
                  for (int v : graph[u]) {
                        if (dist[ pairV[v] ] == INF) {
                              dist[ pairV[v] ] = dist[u] + 1;
                              pq.emplace(pairV[v]);
                        }
                  }
            }
      }
      return dist[NILL] != INF;
}

bool dfs(int u) {
      if (u != NILL) {
            for (int v : graph[u]) {
                  if (dist[ pairV[v] ] == dist[u] + 1) {
                        if (dfs(pairV[v])) {
                              pairU[u] = v;
                              pairV[v] = u;
                              return true;
                        }
                  }
            }
            dist[u] = INF;
            return false;
      }
      return true;
}

int hopcroft_karp() {
      int maxMatch = 0;
      while (bfs()) {
            for (int i = 1; i <= in_left; i++) {
                  if (pairU[i] == NILL and dfs(i)) {
                        maxMatch++;
                  }
            }
      }
      return maxMatch;
}
