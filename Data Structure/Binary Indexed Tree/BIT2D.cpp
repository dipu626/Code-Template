/*
      Binary Indexed Tree - Point Update, Range Query
*/

template <typename T>
struct BIT {
      int row, column;
      vector < vector <T> > res;

      void init(int r, int c) {
            row = r;
            column = c;
            res.clear();
            res.resize(r + 1, vector <T> (c + 1));
      }
      void update(int r, int c, T val) {
            for (int x = r; x <= row; x += (x & -x)) {
                  for (int y = c; y <= column; y += (y & -y)) {
                        res[x][y] += val;
                  }
            }
      }
      T query(int r, int c) {
            T sum = 0;
            for (int x = r; x > 0; x -= (x & -x)) {
                  for (int y = c; y > 0; y -= (y & -y)) {
                        sum += res[x][y];
                  }
            }
            return sum;
      }
      T query(int r1, int c1, int r2, int c2) {
            T v1 = query(r2, c2);
            T v2 = query(r2, c1 - 1);
            T v3 = query(r1 - 1, c2);
            T v4 = query(r1 - 1, c1 - 1);
            return v1 - v2 - v3 + v4;
      }
};
