// Range Update Point Query

template <typename T>
struct BIT {
      int n;
      T Tree;

      void init(int N) {
            n = N;
            Tree = vector <T> (n + 1);
      }
      void update(int pos, T val) {
            while (pos <= n) {
                  Tree[pos] += val;
                  pos += (pos & -pos);
            }
      }
      void update(int l, int r, T val) {
            update(l, val);
            update(r + 1, -val);
      }
      T query(int pos) {
            T sum = 0;
            while (pos > 0) {
                  sum += Tree[pos];
                  pos -= (pos & -pos);
            }
            return sum;
      }
};
