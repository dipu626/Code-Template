/*
  Data Structure  : 2 Dimensional Sparse Table
  Time Complexity : build = O(n m logn logm), query = O(1)
  Space Complexity : O(n m logn logm)
  
  Note : initialize both init(row, col) and initLog()
*/

template <typename T> struct SparseTable2D {
      int n;
      int m;
      vector < vector < vector < vector <T> > > > mat;
      vector <int> LOG;

      void init(int row, int col) {
            n = row;
            m = col;
            int logRow = __lg(row) + 1;
            int logCol = __lg(col) + 1;
            mat.clear(); mat.resize(logRow);
            for (int i = 0; i < logRow; i++) { mat[i].resize(logCol); for (int j = 0; j < logCol; j++) { mat[i][j].resize(row); for (int k = 0; k < row; k++) { mat[i][j][k].resize(col); }  } }
      }
      void initLog(int mx = 300) {
            LOG.clear(); LOG.resize(mx + 1);
            LOG[1] = 0;
            for (int i = 2; i <= mx; i++) {
                  LOG[i] = LOG[i / 2] + 1;
            }
      }
      void build(vector < vector <T> > &arr) {
            for (int i = 0; i < n; i++) {
                  for (int j = 0; j < m; j++) {
                        mat[0][0][i][j] = arr[i][j];
                  }
            }
            for (int p = 0; (1 << p) <= n; p++) {
                  for (int q = 0; (1 << q) <= m; q++) {
                        if (p + q == 0) {
                              continue;
                        }
                        for (int i = 0; i + (1 << p) - 1 < n; i++) {
                              for (int j = 0; j + (1 << q) - 1 < m; j++) {
                                    if (p) {
                                          T x = mat[p - 1][q][i][j];
                                          T y = mat[p - 1][q][i + (1 << (p - 1))][j];
                                          mat[p][q][i][j] = max(x, y);
                                    }
                                    else {
                                          T x = mat[p][q - 1][i][j];
                                          T y = mat[p][q - 1][i][j + (1 << (q - 1))];
                                          mat[p][q][i][j] = max(x, y);
                                    }
                              }
                        }
                  }
            }
      }
      T query(int x1, int y1, int x2, int y2) {
            int x = LOG[x2 - x1 + 1];
            int y = LOG[y2 - y1 + 1];
            x2 = x2 - (1 << x) + 1;
            y2 = y2 - (1 << y) + 1;
            T ans = max({mat[x][y][x1][y1], mat[x][y][x2][y1], mat[x][y][x1][y2], mat[x][y][x2][y2]});
            return ans;
      }
};
