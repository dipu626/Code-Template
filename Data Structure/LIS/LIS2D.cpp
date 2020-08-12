/*
      Problem:
            Find 2D strictly longest increasing subsequence where x1 < x2 and y1 < y2.
      Note:
            Change divideConquer() according to problem statement as increasing and strictly increasing.
      Usage :
            1. Compress all the points coordinate (x and y)
            2. Set initial dp value of a point 1
            3. Initialize BIT
            4. Call divideConquer(1, n)
            5. Calculate maximum dp value of all points

      Complexity : O(n x logn x logn)
*/

struct Node {
      int x, y, id;
      int dp;

      Node(int x = 0, int y = 0, int id = 0, int dp = 1)
            : x(x), y(y), id(id), dp(dp) {}

      bool operator < (const Node &other) {
            if (x == other.x) {
                  return y < other.y;
            }
            return x < other.x;
      }
};

struct BIT {
      int n;
      vector <int> bit;

      void init(int N) {
            n = N;
            bit.clear();      bit.resize(N + 1);
      }
      void update(int pos, int val) {
            while (pos <= n) {
                  bit[pos] = max(bit[pos], val);
                  pos += (pos & -pos);
            }
      }
      int prefixMax(int pos) {
            int maxi = 0;
            while (pos > 0) {
                  maxi = max(maxi, bit[pos]);
                  pos -= (pos & -pos);
            }
            return maxi;
      }
      void recover(int pos) {
            while (pos <= n) {
                  bit[pos] = 0;
                  pos += (pos & -pos);
            }
      }
};

Node points[maxn];
BIT bit;

void divideConquer(int l, int r) {
      if (l >= r) {
            return;
      }
      int mid = l + r >> 1;
      divideConquer(l, mid);
      sort(points + l, points + mid + 1);
      sort(points + mid + 1, points + r + 1);
      int i = l;
      for (int j = mid + 1; j <= r; j++) {
            while (i <= mid and points[i].x < points[j].x) { // Change according to problem statement
                  bit.update(points[i].y, points[i].dp);
                  ++i;
            }
            int prefixMax = bit.prefixMax(points[j].y - 1);
            points[j].dp = max(points[j].dp, prefixMax + 1);
      }
      for (int i = l; i <= mid; i++) {
            bit.recover(points[i].y);
      }
      sort(points + mid + 1, points + r + 1, [&](Node p, Node q) { return p.id < q.id; } );
      divideConquer(mid + 1, r);
}
