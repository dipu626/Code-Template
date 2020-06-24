/*
  Persistent Trie
  
  Problem : Given a rooted tree at root 1 and two nodes U and V. Select subtree rooted at U and
            then from that subtree removes subtree rooted at V.
            Take all numbers of the tree segment and do XOR with Z. Then find the K-th smallest 
            number among the XOR'ed numbers.
            
  Test    : https://toph.co/p/jontrona-of-liakot
*/

static const int maxn = 2e5 + 5;
static const int Max = 6e6 + 6;

struct Node {
      int st;
      int lchild;
      int rchild;
      Node(int st = 0, int lchild = 0, int rchild = 0)
            : st(st), lchild(lchild), rchild(rchild) {}
} Tree[Max];

int version[maxn];
int NODES;

int update(int root, int pos, int val) {
      int newNode = ++NODES;
      Tree[newNode] = Tree[root];
      if (pos < 0) {
            Tree[newNode].st += 1;
            return newNode;
      }
      int bit = (bool)(val & (1 << pos));
      if (bit == 0) {
            Tree[newNode].lchild = update(Tree[newNode].lchild, pos - 1, val);
      }
      else {
            Tree[newNode].rchild = update(Tree[newNode].rchild, pos - 1, val);
      }
      Tree[newNode].st = Tree[ Tree[newNode].lchild ].st + Tree[ Tree[newNode].rchild ].st;
      return newNode;
}

int kth(int root1, int root2, int root3, int root4, int pos, int k, int xor_val) {
      if (pos < 0) {
            return 0;
      }
      bool bit = (bool)(xor_val & (1 << pos));
      int bad = 0;
      if (bit == 0) {
            bad = Tree[ Tree[root4].lchild ].st - Tree[ Tree[root1].lchild ].st -
                  Tree[ Tree[root3].lchild ].st + Tree[ Tree[root2].lchild ].st;
            if (bad < k) {
                  return (1 << pos) + kth(Tree[root1].rchild, Tree[root2].rchild, Tree[root3].rchild, Tree[root4].rchild, pos - 1, k - bad, xor_val);
            }
            else {
                  return kth(Tree[root1].lchild, Tree[root2].lchild, Tree[root3].lchild, Tree[root4].lchild, pos - 1, k, xor_val);
            }
      }
      else {
            bad = Tree[ Tree[root4].rchild ].st - Tree[ Tree[root1].rchild ].st -
                  Tree[ Tree[root3].rchild ].st + Tree[ Tree[root2].rchild ].st;
            if (bad < k) {
                  return (1 << pos) + kth(Tree[root1].lchild, Tree[root2].lchild, Tree[root3].lchild, Tree[root4].lchild, pos - 1, k - bad, xor_val);
            }
            else {
                  kth(Tree[root1].rchild, Tree[root2].rchild, Tree[root3].rchild, Tree[root4].rchild, pos - 1, k, xor_val);
            }
      }
}

void init() {
      NODES = 0;
      for (int i = 0; i < Max; i++) {
            Tree[i] = Node();
      }
}

vector < vector <int> > graph;
int in[maxn];
int out[maxn];
int correspondingNode[maxn];
int dfsTime;

void dfs(int u = 1, int p = -1) {
      in[u] = ++dfsTime;
      correspondingNode[dfsTime] = u;
      for (int v : graph[u]) {
            if (v == p) continue;
            dfs(v, u);
      }
      out[u] = dfsTime;
}

int arr[maxn];

signed main()
{
      ios_base::sync_with_stdio(false);
      cin.tie(nullptr);
      cout.precision(12);

      #ifndef ONLINE_JUDGE
          freopen("in.txt", "r", stdin);
      #endif // ONLINE_JUDGE

      int n, q;
      cin >> n >> q;
      for (int i = 1; i <= n; i++) {
            cin >> arr[i];
      }
      graph.resize(n + 1);
      for (int e = 1; e < n; e++) {
            int u, v;
            cin >> u >> v;
            graph[u].push_back(v);
            graph[v].push_back(u);
      }
      dfs();
      init();
      for (int i = 1; i <= n; i++) {
            version[i] = update(version[i - 1], 30, arr[ correspondingNode[i] ]);
      }
      while (q--) {
            int u, v, z, k;
            cin >> u >> v >> z >> k;
            int root1 = version[ in[u] - 1 ];
            int root2 = version[ in[v] - 1 ];
            int root3 = version[ out[v] ];
            int root4 = version[ out[u] ];
            int sze = out[u] - in[u] + 1 - (out[v] - in[v] + 1);
            if (sze < k) {
                  cout << "-1" << endl;
            }
            else {
                  int ans = kth(root1, root2, root3, root4, 30, k, z);
                  cout << ans << endl;
            }
      }

      #ifndef ONLINE_JUDGE
            cerr << endl << "Time : " << 1.0 * clock() / CLOCKS_PER_SEC << " s." << endl;
      #endif // ONLINE_JUDGE

      return 0;
}
