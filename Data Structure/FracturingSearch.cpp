// Kth minimum spannig tree
// Complexity : O(km), k = kth minimum spanning tree, m = edges
// Problem : 10462 - Is There A Second Way Left?

static const int maxn = 100 + 5;
static const int logn = 18;

struct Edge {
      int u, v, w;
      Edge(int u = 0, int v = 0, int w = 0)
            : u(u), v(v), w(w) {}

      bool operator < (const Edge &other) const {
            return w < other.w;
      }
};

#define vi         vector <int>

struct Partition {
      vi choices;
      int mstCost;
      vi mstEdges;
      Partition(vi choices, int mstCost, vi mstEdges) {
            this->choices = choices;
            this->mstCost = mstCost;
            this->mstEdges = mstEdges;
      }
      friend bool operator < (Partition p, Partition q) {
            return p.mstCost > q.mstCost;
      }
};

int tnode, tedge;
vector <Edge> graph;
int par[maxn];

void makeSet() {
      for (int i = 1; i <= tnode; i++) {
            par[i] = i;
      }
}

int findRep(int r) {
      if (r == par[r]) {
            return r;
      }
      return par[r] = findRep(par[r]);
}

bool unite(int u, int v) {
      int p = findRep(u);
      int q = findRep(v);
      if (p == q) {
            return false;
      }
      par[q] = p;
      return true;
}

Partition createPartition(vi choices) {
      makeSet();
      int take = 0;
      int ptr = 0;
      int mstCost = 0;
      vi mstEdges(tedge + 1, -1);
      for (int i = 0; i < tedge; i++) {
            if (choices[i] == 1) {
                  Edge e = graph[i];
                  unite(e.u, e.v);
                  mstCost += e.w;
                  mstEdges[ptr++] = i;
                  ++take;
            }
      }
      if (take == tnode - 1) {
            return Partition(choices, mstCost, mstEdges);
      }
      for (int i = 0; i < tedge; i++) {
            if (take == tnode - 1) {
                  break;
            }
            if (choices[i] == 0) {
                  Edge e = graph[i];
                  if (unite(e.u, e.v)) {
                        mstCost += e.w;
                        mstEdges[ptr++] = i;
                        ++take;
                  }
            }
      }
      sort(mstEdges.begin(), mstEdges.begin() + ptr);
      if (take == tnode - 1) {
            return Partition(choices, mstCost, mstEdges);
      }
      return Partition(choices, -1, mstEdges);
}

int solve(int k) {
      priority_queue <Partition> pq;
      vi choices(tedge + 1);
      Partition part = createPartition(choices);
      if (part.mstCost == -1) {
            return -1;
      }
      pq.emplace(part);
      while (pq.empty() == false) {
            Partition p = pq.top(); pq.pop();
            --k;
            if (k == 0) {
                  return p.mstCost;
            }
            for (int i = 0; i < tnode-1; i++) {
                  if (p.choices[ p.mstEdges[i] ] == 0) {
                        choices = p.choices;
                        choices[ p.mstEdges[i] ] = -1;
                        for (int j = 0; j < i; j++) {
                              choices[ p.mstEdges[j] ] = 1;
                        }
                        Partition nxt = createPartition(choices);
                        if (nxt.mstCost != -1) {
                              pq.emplace(nxt);
                        }
                  }
            }
      }
      return -2;
}

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
            cin >> tnode >> tedge;
            for (int e = 1; e <= tedge; e++) {
                  int u, v, w;
                  cin >> u >> v >> w;
                  graph.emplace_back(u, v, w);
            }
            sort(graph.begin(), graph.end());
            int mst = solve(2);
            cout << "Case #" << tcase << ": ";
            if (mst == -1) {
                  cout << "No way" << endl;
            }
            else if (mst == -2) {
                  cout << "No second way" << endl;
            }
            else {
                  cout << mst << endl;
            }
            graph.clear();
      }
}
