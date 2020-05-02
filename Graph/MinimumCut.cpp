// Stoer Wagnar Algorithm
// Complexity : O(n^3)

static const int maxn = 200 + 5;

struct StoerWagner
{
      int n;
      vector < vector <int> > cost;
      vector <int> w;
      vector <bool> marged;
      vector <int> bestCut;

      StoerWagner() {}

      void init(int nn) {
            n = nn;
            cost = vector < vector <int> >(n + 1, vector <int> (n + 1));
            w = vector <int> (n + 1);
            marged = vector <bool> (n + 1);
      }
      void addEdge(int u, int v, int c) {
            cost[u][v] += c;
            cost[v][u] += c;
      }
      int minCut() {
            int best = numeric_limits <int>::max();
            marged[1] = true;
            for (int i = 2; i <= n; i++) {
                  marged[i] = false;
            }
            vector <int> cut;
            vector <bool> vis(n);
            for (int phase = 1; phase < n; phase++) {
                  vis[1] = true;
                  for (int i = 2; i <= n; i++) {
                        if (marged[i] == false) {
                              vis[i] = false;
                              w[i] = cost[1][i];
                        }
                  }
                  int prv = 1;
                  int nxt;
                  for (int i = n - 1 - phase; i >= 0; i--) {
                        nxt = -1;
                        for (int j = 2; j <= n; j++) {
                              if (vis[j] == false and (nxt == -1 or w[j] > w[nxt])) {
                                    nxt = j;
                              }
                        }
                        vis[nxt] = true;
                        if (i > 0) {
                              prv = nxt;
                              for (int j = 2; j <= n; j++) {
                                    if (vis[j] == false) {
                                          w[j] += cost[nxt][j];
                                    }
                              }
                        }
                  }
                  for (int i = 1; i <= n; i++) {
                        cost[i][prv] += cost[nxt][i];
                        cost[prv][i] += cost[nxt][i];
                  }
                  marged[nxt] = true;
                  cut.emplace_back(nxt);
                  if (best > w[nxt]) {
                        best = w[nxt];
                        bestCut = cut;
                  }
            }
            return best;
      }
} storewagner;

signed main()
{
      ios_base::sync_with_stdio(false);
      cin.tie(nullptr);

      #ifndef ONLINE_JUDGE
          freopen("in.txt", "r", stdin);
      #endif // ONLINE_JUDGE

      int tc;
      cin >> tc;
      for (int tcase = 1; tcase <= tc; tcase++) {
            int n, m;
            cin >> n >> m;
            storewagner.init(n);
            for (int e = 1; e <= m; e++) {
                  int u, v, w;
                  cin >> u >> v >> w;
                  storewagner.addEdge(u, v, w);
            }
            cout << "Case #" << tcase << ": " << storewagner.minCut() << '\n';
      }
}
