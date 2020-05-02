// Point Update Range Query + Lower Bound in O(logn)

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
      T query(int pos) {
            T sum = 0;
            while (pos > 0) {
                  sum += Tree[pos];
                  pos -= (pos & -pos);
            }
            return sum;
      }
      T query(int l, int r) {
            return query(r) - query(l - 1);
      }
      int lowerBound(T val) {
            T sum = 0;
            int pos = 0;
            for (int i = logn - 1; i >= 0; i--) {
                  int newpos = pos + (1LL << i);
                  if (newpos < n and sum + Tree[newpos] < val) {
                        sum += Tree[newpos];
                        pos = newpos;
                  }
            }
            return pos + 1; // +1 because 'pos' will have position of largest
                            // value less than 'val'
      }
};
