/*
      Caution: use array implementation if gives TLE
*/

template <typename T>
struct DST {
      int n;
      int hgt;
      vector <T> arr;
      vector < vector <T> > dst;

      void init(int N, T *ar) {
            n = N;
            hgt = 1;
            while ((1 << hgt) < n) {
                  hgt++;
            }
            dst.clear();
            dst.resize((1 << hgt) + 5, vector <T> (hgt + 5));
            arr.clear();
            arr.resize((1 << hgt) + 5);
            for (int i = 0; i < n; i++) {
                  arr[i] = ar[i];
            }
      }
      T get(T x, T y) {
            return (x * y) % p;
      }
      void build(int h, int l, int r) {
            if (h < 0) {
                  return;
            }
            int mid = (l + r) / 2;
            ll product = 1;
            for (int i = mid - 1; i >= l; i--) {
                  dst[i][h] = get(product, arr[i]);
                  product = get(product, arr[i]);
            }
            product = 1;
            for (int i = mid; i < r; i++) {
                  dst[i][h] = get(product, arr[i]);
                  product = get(product, arr[i]);
            }
            build(h - 1, l, mid);
            build(h - 1, mid, r);
      }
      void build_dst() {
            build(hgt - 1, 0, 1 << hgt);
      }
      T query(int l, int r) {
            if (l == r) {
                  return arr[l];
            }
            int h = 31 - __builtin_clz(l ^ r);
            return get(dst[l][h], dst[r][h]);
      }
};
