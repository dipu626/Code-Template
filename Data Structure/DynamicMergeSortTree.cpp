/*
  Dynamic Merge Sort Tree
  Use pair <int, int> for multiset
*/

struct MergeSortTree {
      order_set <long long> os;
      MergeSortTree() {
            os.clear();
      }
      void assign_leaf(long long num) {
            os.insert(num);
      }
      void push(long long num) {
            os.insert(num);
      }
      void delet(long long num) {
            auto fnd = os.find(num);
            assert(fnd != os.end());
            os.erase(fnd);
      }
      void marge(const MergeSortTree &lchild, const MergeSortTree &rchild) {
            for (long long x : lchild.os) {
                  os.insert(x);
            }
            for (long long x : rchild.os) {
                  os.insert(x);
            }
      }
      int count_less(long long x) {
            return os.order_of_key(x);
      }
      int count_greater(long long x) {
            return os.size() - os.order_of_key(x + 1);
      }
} mstree[maxn * 4];

long long arr[maxn];

void build(int node, int a, int b) {
      if (a == b) {
            return void(mstree[node].assign_leaf(arr[a]));
      }
      int lchild = node * 2;
      int rchild = lchild + 1;
      int mid = (a + b) / 2;
      build(lchild, a, mid);
      build(rchild, mid + 1, b);
      mstree[node].marge(mstree[lchild], mstree[rchild]);
}

void update(int node, int a, int b, int pos, long long ins_val, long long del_val) {
      if (a == b) {
            mstree[node].delet(del_val);
            mstree[node].push(ins_val);
            return;
      }
      int lchild = node * 2;
      int rchild = lchild + 1;
      int mid = (a + b) / 2;
      if (pos <= mid) {
            update(lchild, a, mid, pos, ins_val, del_val, goes);
      }
      else {
            update(rchild, mid + 1, b, pos, ins_val, del_val, goes);
      }
      mstree[node].delet(del_val);
      mstree[node].push(ins_val);
}

pair <int, int> query(int node, int a, int b, int i, int j, long long x) {
      if (a > j or b < i) {
            return make_pair(0, 0);
      }
      if (a >= i and b <= j) {
            return make_pair(mstree[node].count_greater(x), mstree[node].count_less(x));
      }
      int lchild = node * 2;
      int rchild = lchild + 1;
      int mid = (a + b) / 2;
      pair <int, int> p = query(lchild, a, mid, i, j, x);
      pair <int, int> q = query(rchild, mid + 1, b, i, j, x);
      pair <int, int> res = make_pair(p.first + q.first, p.second + q.second);
      return res;
}
