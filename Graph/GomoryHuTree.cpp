/*
  Problem : 10989 - Bomb, Divide and Conquer
*/

#include "bits/stdc++.h"
#include "ext/pb_ds/assoc_container.hpp"
#include "ext/pb_ds/tree_policy.hpp"

using namespace std;
using namespace __gnu_pbds;

template <typename T> using order_set = tree <T, null_type, less <T>, rb_tree_tag, tree_order_statistics_node_update>;

#define ll          long long int
#define endl        '\n'

static const int maxn = 200 + 5;
static const int logn = 18;
static const ll  inf  = numeric_limits <ll>::max();

struct Node {
      int v, w;
      Node(int v = 0, int w = 0)
            : v(v), w(w) {}
};

vector < vector <int> > graph;
int tnode, tedge;
ll cap[maxn][maxn], flow[maxn][maxn];
int level[maxn], ptr[maxn];
int father[maxn];
ll maxflow[maxn];

bool bfs(int source, int sink) {
      fill(begin(level), end(level), -1);
      queue <int> pq;
      pq.push(source);
      level[source] = 0;
      while (pq.size()) {
            int u = pq.front();
            pq.pop();
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

ll dfs(int u, ll minCap, int sink) {
      if (u == sink) {
            return minCap;
      }
      for (int &i = ptr[u]; i < (int)graph[u].size(); i++) {
            int v = graph[u][i];
            if (level[v] == level[u]+1 && flow[u][v] < cap[u][v]) {
                  ll minFlow = dfs(v, min(minCap, cap[u][v] - flow[u][v]), sink);
                  if (minFlow > 0) {
                        flow[u][v] += minFlow;
                        flow[v][u] -= minFlow;
                        return minFlow;
                  }
            }
      }
      return 0;
}

ll DinicMaxFlow(int source, int sink) {
      int maxFlow = 0;
      while(bfs(source, sink)) {
            memset(ptr, 0, sizeof ptr);
            while(ll bottleneck = dfs(source, inf, sink)) {
                  maxFlow += bottleneck;
            }
      }
      return maxFlow;
}

void clearFlow() {
      for (int i = 1; i <= tnode; i++) {
            for (int j = 1; j <= tnode; j++) {
                  flow[i][j] = 0;
            }
      }
}

ll GomoryTree() {
      ll ans = numeric_limits <ll>::max();
      for (int i = 1; i <= tnode; i++) {
            father[i] = 1;
      }
      for (int i = 2; i <= tnode; i++) {
            clearFlow();
            maxflow[i] = DinicMaxFlow(i, father[i]);
            bfs(i, father[i]);
            for (int j = i + 1; j <= tnode; j++) {
                  if (level[j] != -1 && father[j] == father[i]) {
                        father[j] = i;
                  }
            }
            if (maxflow[i] < ans) {
                  ans = maxflow[i];
            }
      }
      return ans;
}

void init(int n) {
      graph.clear();
      graph.resize(n + 1);
      for (int i = 0; i <= n; i++) {
            for (int j = 0; j <= n; j++) {
                  cap[i][j] = 0;
                  flow[i][j] = 0;
            }
      }
}

signed main()
{
      ios_base::sync_with_stdio(false);
      cin.tie(nullptr);

      #ifndef ONLINE_JUDGE
          freopen("in.txt", "r", stdin);
      #endif // ONLINE_JUDGE

      auto seed = chrono::high_resolution_clock::now().time_since_epoch().count();
      mt19937 mt_rand(seed);

      function <int(int, int)> Rand = [&](int l, int r) {
            int rnd = uniform_int_distribution <int> (l, r)(mt_rand);
            return rnd;
      };

      int tc;
      cin >> tc;
      for (int tcase = 1; tcase <= tc; tcase++) {
            cin >> tnode >> tedge;
            init(tnode);
            for (int e = 1; e <= tedge; e++) {
                  int u, v, w;
                  cin >> u >> v >> w;
                  graph[u].emplace_back(v);
                  graph[v].emplace_back(u);
                  cap[u][v] += w;
                  cap[v][u] += w;
            }
            bfs(1, tnode);
            bool notConnected = false;
            for (int i = 1; i <= tnode; i++) {
                  if (level[i] == -1) {
                        notConnected = true;
                        break;
                  }
            }
            if (notConnected) {
                  cout << "Case #" << tcase << ": 0" << endl;
                  continue;
            }
            ll ans = GomoryTree();
            cout << "Case #" << tcase << ": " << ans << endl;
      }
}
