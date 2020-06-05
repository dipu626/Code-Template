/**
      Online Bridge Searching

      Update : Add an edge
      Query  : Calculate number of bridges in the graph
**/

int n,           // number of nodes
    bridge,      // total bridge after each addition of edge
    m,           // number of edge
    bcc[maxn],   // bcc number of i'th node
    comp[maxn],  // connected component no of i'th node
    link[maxn],  // link of parent node
    sz[maxn];    // size of connected component where i'th node associated

void init() {
      for(int i = 0; i < maxn; i++) {
            bcc[i] = comp[i] = i;  // BCC and CC of a node, Initially all are isolate.
            link[i] = -1;          // Link of the parent in CC
            sz[i] = 1;             // Size of a CC
      }
      bridge = 0;
}

// Output the BCC of a node
int get_bcc(int a) {
      if (a == -1) {
            return -1;
      }
      if (bcc[a] == a) {
            return a;
      }
      return bcc[a] = get_bcc(bcc[a]);
}

// Output the root of the component where a is.
int get_comp(int a)
{
      if (comp[a] == a) {
            return a;
      }
      return comp[a] = get_comp(comp[a]);
}

int cs = 0;
int vis[maxn];

// Merging two path, a->LCA, b->LCA
void merge_path(int a, int b) {
      cs++;
      a = get_bcc(a);
      b = get_bcc(b);
      vector <int> va;
      vector <int> vb;
      int lca = -1;
      while(1) {
            if (a != -1) {
                  a = get_bcc(a);
                  va.emplace_back(a);
                  if (vis[a] == cs) {
                        lca = a;
                        break;
                  }
                  vis[a] = cs;
                  a = link[a];
            }
            if (b != -1) {
                  b = get_bcc(b);
                  vb.emplace_back(b);
                  if (vis[b] == cs) {
                        lca = b;
                        break;
                  }
                  vis[b] = cs;
                  b = link[b];
            }
      }
      for (int it : va) {
            bcc[it] = lca;    // compressing in same BCC
            if (it == lca) {
                  break;
            }
            bridge--;
      }
      for (int it : vb) {
            bcc[it] = lca;   // compressing in same BCC
            if (it == lca) {
                  break;
            }
            bridge--;
      }
}

// This reverses the edge of A to root of the connected component
void make_root(int a) {
      int root = a;
      int child = -1;
      while (a != -1) {
            int p = get_bcc(link[a]);
            link[a] = child;
            comp[a] = root;
            child = a;
            a = p;
      }
      sz[root] = sz[child];
}

void add_edge(int a, int b) {
      a = get_bcc(a);
      b = get_bcc(b);
      if (a == b) {           // Case 1
            return;
      }
      int u = get_comp(a);
      int v = get_comp(b);
      if (u != v) {            // Case 2
            bridge++;
            if (sz[u] > sz[v]) {
                  swap(a, b);
                  swap(u, v);
            }
            make_root(a);
            link[a] = comp[a] = b;
            sz[v] += sz[a];
      }
      else {                  // Case 3
            merge_path(a, b);
      }
}

signed main()
{
      init();

      cin >> n >> m;
      for (int e = 1; e <= m; e++) {
            int u, v;
            cin >> u >> v;
            add_edge(u, v);
            cout << bridge << endl;
      }
}
