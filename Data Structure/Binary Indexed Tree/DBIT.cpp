/**
 * Description  : range sum queries and point updates for $D$ dimensions
 * Source       : https://codeforces.com/blog/entry/64914
 * Verification : SPOJ matsum, Timus - 1470. UFOs
 * Usage        : {BIT<int, 10, 10>} gives 2D BIT
 * Update       : fenwick.upd(x, y, val)
 * Query        : fenwick.query(x1, x2, y1, y2) in 2D
 * Time         : O((log N)^D)
 *
 * Note         : declare ds global, if there are multiple test-cases clear
 *                the cell after each test cases.
**/

template <class T, int ...Ns> struct BIT {
      T val = 0;
      void upd(T v) { val += v; }
      T query() { return val; }
};

template <class T, int N, int... Ns> struct BIT <T, N, Ns...> {
      BIT <T,Ns...> bit[N + 1]; // use map if N is large enough
      template <typename... Args> void upd(int pos, Args... args) {
            assert(pos > 0);
            for ( ; pos <= N; pos += pos & -pos) {
                  bit[pos].upd(args...);
            }
      }
      template <typename... Args> T sum(int r, Args... args) {
            T res = 0;
            for ( ; r; r -= r & -r) {
                  res += bit[r].query(args...);
            }
            return res;
      }
      template <typename... Args> T query(int l, int r, Args... args) {
            return sum(r, args...) - sum(l - 1, args...);
      }
};
