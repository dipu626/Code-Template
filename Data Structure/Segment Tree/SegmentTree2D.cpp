static const int maxn = 500 + 5;

ll grid[maxn][maxn];

template <typename T>
struct Node {
      T sum, maxi, mini;
      Node(T sum = 0, T maxi = numeric_limits <T>::min(), T mini = numeric_limits <T>::max())
           : sum(sum), maxi(maxi), mini(mini) {}
};

template <typename T>
struct SegmentTree2D {
      #define Node        Node <T>

      int row, column;
      vector < vector <Node> > st;

      void init(int r, int c) {
            row = r;
            column = c;
            st.resize(4 * r, vector <Node> (4 * c));
      }
      void gen_segtree_from_c1_to_c2(int parSegTree, int r1, int r2, int node, int c1, int c2) {
            if (c1 == c2) {
                  if (r1 == r2) {
                        st[parSegTree][node].sum = grid[r1][c1];
                        st[parSegTree][node].maxi = grid[r1][c1];
                        st[parSegTree][node].mini = grid[r1][c1];
                        return;
                  }
                  if (r1 != r2) {
                        int lchild = parSegTree * 2;
                        int rchild = lchild + 1;
                        st[parSegTree][node].sum = st[lchild][node].sum + st[rchild][node].sum;
                        st[parSegTree][node].maxi = max(st[lchild][node].maxi, st[rchild][node].maxi);
                        st[parSegTree][node].mini = min(st[lchild][node].mini, st[rchild][node].mini);
                        return;
                  }
            }
            int left = node * 2;
            int right = left + 1;
            int mid = (c1 + c2) / 2;
            gen_segtree_from_c1_to_c2(parSegTree, r1, r2, left, c1, mid);
            gen_segtree_from_c1_to_c2(parSegTree, r1, r2, right, mid+1, c2);
            st[parSegTree][node].sum = st[parSegTree][left].sum + st[parSegTree][right].sum;
            st[parSegTree][node].maxi = max(st[parSegTree][left].maxi, st[parSegTree][right].maxi);
            st[parSegTree][node].mini = min(st[parSegTree][left].mini, st[parSegTree][right].mini);
      }
      void gen_segtree_from_r1_to_r2(int node, int r1, int r2) {
            if (r1 == r2) {
                  gen_segtree_from_c1_to_c2(node, r1, r2, 1, 1, column);
                  return;
            }
            int left = node * 2;
            int right = left + 1;
            int mid = (r1 + r2) >> 1;
            gen_segtree_from_r1_to_r2(left, r1, mid);
            gen_segtree_from_r1_to_r2(right, mid+1, r2);
            gen_segtree_from_c1_to_c2(node, r1, r2, 1, 1, column);
      }
      void update_segtree_in_cx(int parSegTree, int r1, int r2, int node, int c1, int c2, int y, ll value, bool is_add = 0) {
            if (c1 > c2 or c1 > y or c2 < y) {
                  return;
            }
            if (c1 >= y and c2 <= y) {
                  if (r1 == r2) {
                        if (is_add) {
                              st[parSegTree][node].sum += value;
                              st[parSegTree][node].maxi += value;
                              st[parSegTree][node].mini += value;
                        }
                        else {
                              st[parSegTree][node].sum = value;
                              st[parSegTree][node].maxi = value;
                              st[parSegTree][node].mini = value;
                        }
                        return;
                  }
                  if (r1 != r2) {
                        int lchild = parSegTree * 2;
                        int rchild = lchild + 1;
                        st[parSegTree][node].sum = st[lchild][node].maxi + st[rchild][node].sum;
                        st[parSegTree][node].maxi = max(st[lchild][node].maxi, st[rchild][node].maxi);
                        st[parSegTree][node].mini = min(st[lchild][node].mini, st[rchild][node].mini);
                        return;
                  }
            }
            int left = node * 2;
            int right = left + 1;
            int mid = (c1 + c2) >> 1;
            update_segtree_in_cx(parSegTree, r1, r2, left, c1, mid, y, value, is_add);
            update_segtree_in_cx(parSegTree, r1, r2, right, mid + 1, c2, y, value, is_add);
            st[parSegTree][node].sum = st[parSegTree][left].maxi + st[parSegTree][right].sum;
            st[parSegTree][node].maxi = max(st[parSegTree][left].maxi, st[parSegTree][right].maxi);
            st[parSegTree][node].mini = min(st[parSegTree][left].mini, st[parSegTree][right].mini);
      }
      void update_segtree(int node, int r1, int r2, int x, int y, ll value, bool is_add = 0) {
            if (r1 > r2 or r1 > x or r2 < x) {
                        return;
            }
            if (r1 >= x and r2 <= x) {
                  update_segtree_in_cx(node, r1, r2, 1, 1, column, y, value, is_add);
                  return;
            }
            int left = node * 2;
            int right = left + 1;
            int mid = (r1 + r2) >> 1;
            update_segtree(left, r1, mid, x, y, value, is_add);
            update_segtree(right, mid+1, r2, x, y, value, is_add);
            update_segtree_in_cx(node, r1, r2, 1, 1, column, y, value, is_add);
      }
      Node query_from_c1_to_c2(int parSegTree, int node, int c1, int c2, int i, int j) {
            if (c1 > c2 or c1 > j or c2 < i) {
                  return Node();
            }
            if (c1 >= i and c2 <= j) {
                  return st[parSegTree][node];
            }
            int left = node * 2;
            int right = left + 1;
            int mid = (c1 + c2) >> 1;
            Node p = query_from_c1_to_c2(parSegTree, left, c1, mid, i, j);
            Node q = query_from_c1_to_c2(parSegTree, right, mid + 1, c2, i, j);
            Node res;
            res.sum = p.sum + q.sum;
            res.maxi = max(p.maxi, q.maxi);
            res.mini = min(p.mini, q.mini);
            return res;
      }
      Node query_from_r1_to_r2(int node, int r1, int r2, int ri, int rj, int ci, int cj) {
            if (r1 > r2 or r1 > rj or r2 < ri) {
                  return Node();
            }
            if (r1 >= ri and r2 <= rj) {
                  return query_from_c1_to_c2(node, 1, 1, column, ci, cj);
            }
            int left = node * 2;
            int right = left + 1;
            int mid = (r1 + r2) >> 1;
            Node p = query_from_r1_to_r2(left, r1, mid, ri, rj, ci, cj);
            Node q = query_from_r1_to_r2(right, mid + 1, r2, ri, rj, ci, cj);
            Node res;
            res.sum = p.sum + q.sum;
            res.maxi = max(p.maxi, q.maxi);
            res.mini = min(p.mini, q.mini);
            return res;
      }
      void build() {
            gen_segtree_from_r1_to_r2(1, 1, row);
      }
      void uadd(int x, int y, ll val) {
          update_segtree(1, 1, row, x, y, val, 1);
      }
      void uset(int x, int y, ll val) {
            update_segtree(1, 1, row, x, y, val, 0);
      }
      Node query(int r1, int c1, int r2, int c2) {
            return query_from_r1_to_r2(1, 1, row, r1, r2, c1, c2);
      }
      /*
      T get_sum(int r1, int c1, int r2, int c2) {
            return query(int r1, int c1, int r2, int c2).sum;
      }
      T get_maxi(int r1, int c1, int r2, int c2) {
            return query(int r1, int c1, int r2, int c2).maxi;
      }
      T get_mini(int r1, int c1, int r2, int c2) {
            return query(int r1, int c1, int r2, int c2).mini;
      }
      */
      #undef Node
};
