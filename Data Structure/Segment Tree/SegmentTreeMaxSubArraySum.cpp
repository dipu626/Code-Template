/*
  Data Structure : Find maximum subarray sum in an array with point update
  Complexity     : Query = O(logn), Update = O(logn)

  Note : Change Constructore according to problem statement.

         It returns original value rather than 0 if we don't have a subarray of
         positive value.

  Test : Spoj - GSS1
         https://cses.fi/problemset/task/1190/
*/

template <typename T>
struct MaxSubArraySumNode {
      T prefixMaxSum;
      T suffixMaxSum;
      T maxSum;
      T sum;
      bool outRange;

      MaxSubArraySumNode(bool outRange = 0)
            : prefixMaxSum(0), suffixMaxSum(0), maxSum(0), sum(0), outRange(outRange) {}

      void assignLeaf(T num) {
            prefixMaxSum = num;
            suffixMaxSum = num;
            maxSum = num;
            sum = num;
      }
      void marge(MaxSubArraySumNode &lchild, MaxSubArraySumNode &rchild) {
            if (lchild.outRange == true) {
                  *this = rchild;
            }
            else if (rchild.outRange == true) {
                  *this = lchild;
            }
            else {
                  sum = lchild.sum + rchild.sum;
                  prefixMaxSum = max(lchild.prefixMaxSum, lchild.sum + rchild.prefixMaxSum);
                  suffixMaxSum = max(rchild.suffixMaxSum, rchild.sum + lchild.suffixMaxSum);
                  maxSum = max({prefixMaxSum, suffixMaxSum, lchild.maxSum, rchild.maxSum, lchild.suffixMaxSum + rchild.prefixMaxSum});
            }
      }
      T getMax() {
            return max({prefixMaxSum, suffixMaxSum, maxSum, sum});
      }
};

template <typename T>
struct MaxSubArraySumSegmentTree {
      #define Node              MaxSubArraySumNode <T>
      #define lchild            node * 2
      #define rchild            node * 2 + 1
      #define mid               (a + b) / 2

      int n;
      vector <Node> st;

      void init(int N) {
            n = N;
            st.clear();       st.resize(4 * N + 5);
      }
      void build(int arr[], int node, int a, int b) {
            if (a == b) {
                  st[node].assignLeaf(arr[a]);
                  return;
            }
            build(arr, lchild, a, mid);
            build(arr, rchild, mid + 1, b);
            st[node].marge(st[lchild], st[rchild]);
      }
      void update(int node, int a, int b, int pos, T nval) {
            if (a > pos or b < pos) {
                  return;
            }
            if (a >= pos and b <= pos) {
                  st[node].assignLeaf(nval);
                  return;
            }
            update(lchild, a, mid, pos, nval);
            update(rchild, mid + 1, b, pos, nval);
            st[node].marge(st[lchild], st[rchild]);
      }
      Node query(int node, int a, int b, int i, int j) {
            if (a > j or b < i) {
                  return Node(1);
            }
            if (a >= i and b <= j) {
                  return st[node];
            }
            Node p = query(lchild, a, mid, i, j);
            Node q = query(rchild, mid + 1, b, i, j);
            Node res;
            res.marge(p, q);
            return res;
      }
      void build(int arr[]) {
            build(arr, 1, 1, n);
      }
      void update(int pos, T nval) {
            update(1, 1, n, pos, nval);
      }
      T getMax(int l, int r) {
            return query(1, 1, n, l, r).getMax();
      }

      #undef Node
      #undef lchild
      #undef rchild
      #undef mid
};
