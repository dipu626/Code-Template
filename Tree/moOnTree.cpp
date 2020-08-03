/*
  Algorithm : Mo's Algorithm on Tree
  Tutorial  : https://codeforces.com/blog/entry/43230
              https://codeforces.com/blog/entry/68271
              
  Complexity : O(q . sqrt(n)), block = sqrt(n)
  
  Problem : F. Frank Sinatra
  OJ      : https://codeforces.com/gym/100962
  
  Problem : You are given a bidirectional graph T which is a tree consisting of N vertices and N − 1 edges.
            Each edge of the tree is associated with some non-negative integer Xi.
            Your task has a very simple description. You are given q queries. In j-th, query you have to find
            the smallest non-negative integer Y that is not present in the set of all integers associated with
            edges of the simple path between vertices Aj and Bj.
*/

struct Node {
      int v, w;
      Node(int v = 0, int w = 0)
            : v(v), w(w) {}
};

struct Mo {
      int l, r, id;
      Mo(int l = 0, int r = 0, int id = 0)
            : l(l), r(r), id(id) {}

      friend bool operator < (Mo p, Mo q) {
            int pb = p.l / block;
            int qb = q.l / block;
            if (pb != qb) {
                  return p.l < q.l;
            }
            return (p.r < q.r) ^ (p.l / block % 2);
      }
} queries[maxn];

vector <Node> graph[maxn];
int nodeVal[maxn];
int dfsTime;
int in[maxn];
int out[maxn];
int correspondingNode[maxn * 2];

int l = 1;
int r = 0;
int ans[maxn];

int box[maxn];    // stores number of distinct integer in the range [L,R]
int fre[maxn];    // frequency of each element
int vis[maxn];    // check a node already visited or not

void dfs(int u = 1, int p = 0) {
      dfsTime++;
      in[u] = dfsTime;
      correspondingNode[dfsTime] = u;
      for (Node it : graph[u]) {
            int v = it.v;
            int w = it.w;
            if (v == p) {
                  continue;
            }
            nodeVal[v] = w;
            dfs(v, u);
      }
      dfsTime++;
      out[u] = dfsTime;
      correspondingNode[dfsTime] = u;
}

void work(int pos) {
      int u = correspondingNode[pos];
      int w = nodeVal[u];
      if (w >= maxn) {  // Out of BOX, larger than this value can never be a result
            return;
      }
      if (vis[u]) {
            if (fre[w] == 1) {
                  box[ w / block ]--;
            }
            fre[w]--;
            vis[u] = 0;
      }
      else {
            if (fre[w] == 0) {
                  box[ w / block ]++;
            }
            fre[w]++;
            vis[u] = 1;
      }
}

void solve() {
      int n, q;
      cin >> n >> q;
      for (int e = 1; e < n; e++) {
            int u, v, w;
            cin >> u >> v >> w;
            graph[u].push_back(Node(v, w));
            graph[v].push_back(Node(u, w));
      }
      dfs(1);
      for (int i = 0; i < q; i++) {
            int u, v;
            cin >> u >> v;
            if (in[u] > in[v]) {
                  swap(u, v);
            }
            queries[i].l = in[u] + 1;
            queries[i].r = in[v];
            queries[i].id = i;
      }
      sort(queries, queries + q);
      l = 1;
      r = 0;
      for (int i = 0; i < q; i++) {
            int L = queries[i].l;
            int R = queries[i].r;
            int ID = queries[i].id;
            while (l > L) work(--l);
            while (r < R) work(++r);
            while (l < L) work(l++);
            while (r > R) work(r--);

            int b;  // find box
            for (int k = 0; ; k++) {
                  if (box[k] < block) {
                        b = k;
                        break;
                  }
            }
            for (int k = b * block; ; k++) {
                  if (fre[k] == 0) {
                        ans[ID] = k;
                        break;
                  }
            }
      }
      for (int i = 0; i < q; i++) {
            cout << ans[i] << endl;
      }
}
