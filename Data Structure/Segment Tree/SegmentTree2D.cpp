static const int maxn = 500 + 5;

ll grid[maxn][maxn];

template <typename T>
struct SegmentTree2D {
      #define pll         pair <ll, ll>
      #define ff          first
      #define ss          second
      #define inf         1e7

      int row, column;
      vector < vector <pll> > st;

      void init(int r, int c) {
            row = r;
            column = c;
            st.resize(4 * r, vector <pll> (4 * c));
      }
      // here we are not changing first 3 arguments. Means, our rows are fixed.
      // we narrow down to our columns, and generate segment tree for row [r1,r2] (including)
      // we can pass flag instead of passing two parameters r1 and r2 (thats just optimization)
      void gen_segtree_from_c1_to_c2(int parSegTree, int r1, int r2, int node, int c1, int c2) {
            if (c1 == c2) {
                  if (r1 == r2) {
                        // means we are working on single row,
                        // and we can directly generate segment tree for that row = r1;
                        st[parSegTree][node].ff = st[parSegTree][node].ss = grid[r1][c1];
                        return;
                  }
                  // here, parSegTree      = parent segment tree
                  // (parSegTree * 2)     = left child segment tree
                  // (parSegTree * 2 + 1) = right child segment tree
                  // we build parent segment tree using values of children segment trees

                  // we are creating segment tree which contains sum from row (r1 to r2)
                  if (r1 != r2) {
                        int lchild = parSegTree * 2;
                        int rchild = lchild + 1;
                        st[parSegTree][node].ff = min(st[lchild][node].ff, st[rchild][node].ff);
                        st[parSegTree][node].ss = max(st[lchild][node].ss, st[rchild][node].ss);
                        return;
                  }
            }
            int left = node * 2;
            int right = left + 1;
            int mid = (c1 + c2) >> 1;
            gen_segtree_from_c1_to_c2(parSegTree, r1, r2, left, c1, mid);
            gen_segtree_from_c1_to_c2(parSegTree, r1, r2, right, mid+1, c2);
            st[parSegTree][node].ff = min(st[parSegTree][left].ff, st[parSegTree][right].ff);
            st[parSegTree][node].ss = max(st[parSegTree][left].ss, st[parSegTree][right].ss);
      }
      void gen_segtree_from_r1_to_r2(int node, int r1, int r2) {
            // if we have narrow down to single row
            if (r1 == r2) {
                  gen_segtree_from_c1_to_c2(node, r1, r2, 1, 1, column);
                  return;
            }
            int left = node * 2;
            int right = left + 1;
            int mid = (r1 + r2) >> 1;
            gen_segtree_from_r1_to_r2(left, r1, mid);
            gen_segtree_from_r1_to_r2(right, mid+1, r2);
            // now using upper two segment trees, we create new segment tree
            gen_segtree_from_c1_to_c2(node, r1, r2, 1, 1, column);
      }
      void build() {
            gen_segtree_from_r1_to_r2(1, 1, row);
      }

      void update_segtree_in_cx(int parSegTree, int r1, int r2, int node, int c1, int c2, int y, ll value) {
            if (c1 > c2 or c1 > y or c2 < y) {
                  return;
            }
            if (c1 >= y and c2 <= y) {
                  if (r1 == r2) {
                        st[parSegTree][node].ff = st[parSegTree][node].ss = value;
                        return;
                  }
                  if (r1 != r2) {
                        int lchild = parSegTree * 2;
                        int rchild = lchild + 1;
                        st[parSegTree][node].ff = min(st[lchild][node].ff, st[rchild][node].ff);
                        st[parSegTree][node].ss = max(st[lchild][node].ss, st[rchild][node].ss);
                        return;
                  }
            }
            int left = node * 2;
            int right = left + 1;
            int mid = (c1 + c2) >> 1;
            update_segtree_in_cx(parSegTree, r1, r2, left, c1, mid, y, value);
            update_segtree_in_cx(parSegTree, r1, r2, right, mid + 1, c2, y, value);
            st[parSegTree][node].ff = min(st[parSegTree][left].ff, st[parSegTree][right].ff);
            st[parSegTree][node].ss = max(st[parSegTree][left].ss, st[parSegTree][right].ss);
      }
      void update_segtree(int node, int r1, int r2, int x, int y, ll value) {
            if (r1 > r2 or r1 > x or r2 < x) {
                        return;
            }
            if (r1 >= x and r2 <= x) {
                  update_segtree_in_cx(node, r1, r2, 1, 1, column, y, value);
                  return;
            }
            int left = node * 2;
            int right = left + 1;
            int mid = (r1 + r2) >> 1;
            update_segtree(left, r1, mid, x, y, value);
            update_segtree(right, mid+1, r2, x, y, value);
            update_segtree_in_cx(node, r1, r2, 1, 1, column, y, value);
      }
      void update(int x, int y, ll value) {
          update_segtree(1, 1, row, x, y, value);
      }

      pll query_from_c1_to_c2(int parSegTree, int node, int c1, int c2, int i, int j) {
            if (c1 > c2 or c1 > j or c2 < i) {
                  return {inf, -inf};
            }
            if (c1 >= i and c2 <= j) {
                  return st[parSegTree][node];
            }
            int left = node * 2;
            int right = left + 1;
            int mid = (c1 + c2) >> 1;
            pll p = query_from_c1_to_c2(parSegTree, left, c1, mid, i, j);
            pll q = query_from_c1_to_c2(parSegTree, right, mid + 1, c2, i, j);
            return {min(p.ff, q.ff), max(p.ss, q.ss)};
      }
      pll query_from_r1_to_r2(int node, int r1, int r2, int ri, int rj, int ci, int cj) {
            if (r1 > r2 or r1 > rj or r2 < ri) {
                  return {inf, -inf};
            }
            if (r1 >= ri and r2 <= rj) {
                  return query_from_c1_to_c2(node, 1, 1, column, ci, cj);
            }
            int left = node * 2;
            int right = left + 1;
            int mid = (r1 + r2) >> 1;
            pll p = query_from_r1_to_r2(left, r1, mid, ri, rj, ci, cj);
            pll q = query_from_r1_to_r2(right, mid + 1, r2, ri, rj, ci, cj);
            return {min(p.ff, q.ff), max(p.ss, q.ss)};
      }
      pll query(int r1, int c1, int r2, int c2) {
            return query_from_r1_to_r2(1, 1, row, r1, r2, c1, c2);
      }

      #undef pll
      #undef ff
      #undef ss
      #undef inf

};
