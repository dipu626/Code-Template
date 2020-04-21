template <typename T>
struct SparseTable
{
      int n;
      vector < vector <T> > Table;

      void init(int N) {
            n = N;
            Table.clear();
            Table.resize(logn, vector <T> (n));
      }
      void build(T *arr) {
            for (int i = 0; i < n; i++) Table[0][i] = arr[i];
            for (int k = 1; (1 << k) <= n; k++) {
                  for (int i = 0; i + (1 << (k - 1)) < n; i++) {
                        T x = Table[k - 1][i];
                        T y = Table[k - 1][i + (1 << (k - 1))];
                        Table[k][i] = min(x, y);
                  }
            }
      }
      T query(int i, int j) {
            int k = log2(j - i + 1);
            T x = Table[k][i];
            T y = Table[k][j + 1 - (1 << k)];
            return min(x, y);
      }
};
