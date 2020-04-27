/*
  Binary Indexed Tree 2D - Range Update Range Query
*/

template <typename T>
struct BIT {
      #define vt         vector < vector <T> >

      int row, column;
      vt A, B, C, D;

      void init(int r, int c) {
            row = r;
            column = c;
            A.clear(); A.resize(r + 1, vector <T> (c + 1));
            B.clear(); B.resize(r + 1, vector <T> (c + 1));
            C.clear(); C.resize(r + 1, vector <T> (c + 1));
            D.clear(); D.resize(r + 1, vector <T> (c + 1));
      }
      void update(vt &res, int r, int c, T val) {
            for (int x = r; x <= row; x +=(x & -x)) {
                  for (int y = c; y <= column; y += (y & -y)) {
                        res[x][y] += val;
                  }
            }
      }
      void prefix_update(int r, int c, T val) {
            update(A, 1, 1, val);

            update(A, 1, c + 1, -val);
            update(B, 1, c + 1, val * c);

            update(A, r + 1, 1, -val);
            update(C, r + 1, 1, val * r);

            update(A, r + 1, c + 1, val);
            update(B, r + 1, c + 1, -val * c);
            update(C, r + 1, c + 1, -val * r);
            update(D, r + 1, c + 1, val * r * c);
      }
      T prefix_query(int rr, int cc) {
            T a, b, c, d;
            a = b = c = d = 0;
            for (int x = rr; x > 0; x -= (x & -x)) {
                  for (int y = cc; y > 0; y -= (y & -y)) {
                        a += A[x][y];
                        b += B[x][y];
                        c += C[x][y];
                        d += D[x][y];
                  }
            }
            return a * rr * cc + b * rr + c * cc + d;
      }
      void range_update(int r1, int c1, int r2, int c2, T val) {
            prefix_update(r2, c2, val);
            prefix_update(r1 - 1, c2, -val);
            prefix_update(r2, c1 - 1, -val);
            prefix_update(r1 - 1, c1 - 1, val);
      }
      T range_query(int r1, int c1, int r2, int c2) {
            T v1 = prefix_query(r2, c2);
            T v2 = prefix_query(r1 - 1, c2);
            T v3 = prefix_query(r2, c1 - 1);
            T v4 = prefix_query(r1 - 1, c1 - 1);
            return v1 - v2 - v3 + v4;
      }
};
