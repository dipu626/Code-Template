struct WaveletTree {
      #define vi       vector <int>
      #define pb       push_back

      int lo, hi;
      WaveletTree *lchild, *rchild;
      vi box;

      WaveletTree(int *from, int *to, int x, int y) {
            lo = x;
            hi = y;
            if (from >= to or lo == hi) {
                  return;
            }
            int mid = (lo + hi) / 2;
            auto f = [mid](int x) {
                  return x <= mid;
            };
            box.reserve(to - from + 1);
            box.pb(0); // for making 1-indexed
            for (auto it = from; it != to; it++) {
                  box.pb(box.back() + f(*it));
            }
            auto pivot = stable_partition(from, to, f);
            lchild = new WaveletTree(from, pivot, lo, mid);
            rchild = new WaveletTree(pivot, to, mid + 1, hi);
      }
      int LTE(int l, int r, int k) {
            if (l > r or k < lo) {
                  return 0;
            }
            if (hi <= k) {
                  return (r - l + 1);
            }
            int lb = box[l - 1];
            int rb = box[r];
            return this->lchild->LTE(lb + 1, rb, k) + this->rchild->LTE(l - lb, r - rb, k);
      }
      int EQL(int l, int r, int k) {
            if (l > r or k < lo or k > hi) {
                  return 0;
            }
            if (lo == hi) {
                  return (r - l + 1);
            }
            int lb = box[l - 1];
            int rb = box[r];
            int mid = (lo + hi) / 2;
            if (k <= mid) {
                  return this->lchild->EQL(lb + 1, rb, k);
            }
            else {
                  return this->rchild->EQL(l - lb, r - rb, k);
            }
      }
      int kth(int l, int r, int k) {
            if (l > r) {
                  return 0;
            }
            if (lo == hi) {
                  return lo;
            }
            int lb = box[l - 1];
            int rb = box[r];
            int inLeft = rb - lb;
            if (k <= inLeft) {
                  return this->lchild->kth(lb + 1, rb, k);
            }
            else {
                  return this->rchild->kth(l - lb, r - rb, k - inLeft);
            }
      }
      ~WaveletTree()
      {
            delete lchild;
            delete rchild;
      }
};

/* Usage:
            WaveletTree *wt;
            wt = new WaveletTree(arr + 1, arr + n + 1, lo, hi)
            lo = minimum element of the array
            hi = maximum element of the array
*/
