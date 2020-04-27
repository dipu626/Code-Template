template <typename T>
struct Node {
      T sum;
      T maxi;
      T mini;
      bool toset;
      bool toadd;
      T lazy;
      Node(T sum = 0, T maxi = numeric_limits <T>::min(), T mini = numeric_limits <T>::max(),
           bool toset = 0, bool toadd = 0, T lazy = 0)
           : sum(sum), maxi(maxi), mini(mini), toset(toset), toadd(toadd), lazy(lazy) {}
};

ll arr[maxn];

template <typename T>
struct SegmentTree {
      #define Node             Node <T>
      #define lchild           node * 2
      #define rchild           node * 2 + 1
      #define mid              (int)(a + b) / 2

      int n;
      vector <Node> st;

      void init(int N) {
            n = N;
            st.clear();
            st.resize(4 * N + 5);
      }
      void marge(int node, int a, int b) {
            st[node].sum = st[lchild].sum + st[rchild].sum;
            st[node].maxi = max(st[lchild].maxi, st[rchild].maxi);
            st[node].mini = min(st[lchild].mini, st[rchild].mini);
      }
      void build(int node, int a, int b) {
            if (a == b) {
                  int val = arr[a];
                  st[node].sum = val;
                  st[node].maxi = val;
                  st[node].mini = val;
                  return;
            }
            build(lchild, a, mid);
            build(rchild, mid + 1, b);
            marge(node, a, b);
      }
      void propagate1(int node, int a, int b) {
            if (a != b) {
                  st[lchild].toset = st[rchild].toset = 1;
                  st[lchild].toadd = st[rchild].toadd = 0;
                  st[lchild].lazy = st[rchild].lazy = st[node].lazy;
            }
            st[node].maxi = st[node].mini = st[node].lazy;
            st[node].sum = 1LL * (b - a + 1) * st[node].lazy;
            st[node].toset = st[node].toadd = 0;
            st[node].lazy = 0;
      }
      void propagate2(int node, int a, int b) {
            if (a != b) {
                  st[lchild].toadd = st[rchild].toadd = 1;
                  st[lchild].lazy += st[node].lazy;
                  st[rchild].lazy += st[node].lazy;
            }
            st[node].sum += 1LL * (b - a + 1) * st[node].lazy;
            st[node].maxi += st[node].lazy;
            st[node].mini += st[node].lazy;
            st[node].toadd = st[node].toset = 0;
            st[node].lazy = 0;
      }
      void update(int node, int a, int b, int i, int j, T val, bool toset) {
            if (st[node].toset) {
                  propagate1(node, a, b);
            }
            if (st[node].lazy) {
                  propagate2(node, a, b);
            }
            if (a > j or b < i) {
                  return;
            }
            if (a >= i and b <= j) {
                  if (toset) {
                        st[node].toset = 1;
                        st[node].toadd = 0;
                        st[node].lazy = val;
                        propagate1(node, a, b);
                  }
                  else {
                        st[node].toset = 0;
                        st[node].toadd = 1;
                        st[node].lazy += val;
                        propagate2(node, a, b);
                  }
                  return;
            }
            update(lchild, a, mid, i, j, val, toset);
            update(rchild, mid + 1, b, i, j, val, toset);
            marge(node, a, b);
      }
      Node query(int node, int a, int b, int i, int j) {
            if (st[node].toset) {
                  propagate1(node, a, b);
            }
            if (st[node].toadd) {
                  propagate2(node, a, b);
            }
            if (a > j or b < i) {
                  return Node();
            }
            if (a >= i and b <= j) {
                  return st[node];
            }
            Node p = query(lchild, a, mid, i, j);
            Node q = query(rchild, mid + 1, b, i, j);
            Node res;
            res.sum = p.sum + q.sum;
            res.maxi = max(p.maxi, q.maxi);
            res.mini = min(p.mini, q.mini);
            marge(node, a, b);
            return res;
      }
      void build() {
            build(1, 1, n);
      }
      void uset(int l, int r, T val) {
            update(1, 1, n, l, r, val, 1);
      }
      void uadd(int l, int r, T val) {
            update(1, 1, n, l, r, val, 0);
      }
      Node query(int l, int r) {
            return query(1, 1, n, l, r);
      }
      T get_sum(int l, int r) {
            return query(l, r).sum;
      }
      T get_maxi(int l, int r) {
            return query(l, r).maxi;
      }
      T get_mini(int l, int r) {
            return query(l, r).mini;
      }
      
      #undef lchild
      #undef rchild
      #undef mid
};
