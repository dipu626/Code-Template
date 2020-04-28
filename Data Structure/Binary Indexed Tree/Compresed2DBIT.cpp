/*
  Problem : https://csacademy.com/contest/archive/task/rectangle-fit/statement/
  Insert  : Add 1 to a point
  Remove  : Subtract 1 to a point
  Query   : Sum of all points in a rectangle starting at (0, 0)
*/

#include "bits/stdc++.h"
#include "ext/pb_ds/assoc_container.hpp"
#include "ext/pb_ds/tree_policy.hpp"

using namespace std;
using namespace __gnu_pbds;

#define pii           pair <int, int>
#define piii          pair <pii, int>
#define mk            make_pair

template <typename T> using orderset = tree <T, null_type, less <T>, rb_tree_tag, tree_order_statistics_node_update>;

static const int maxn = 1e6 + 5;

int N = 1000000;
orderset <piii> bit[maxn]; // use pii for unique point
int ptr;

void Insert(int x, int y) {
      for (int i = x; i <= N; i += (i & -i)) {
            bit[i].insert(mk(mk(y, x), ++ptr));
      }
}

void Remove(int x, int y) {
      for (int i = x; i <= N; i += (i & -i)) {
            bit[i].erase(mk(mk(y, x), -1));
      }
}

int query(int x, int y) {
      int ans = 0;
      for (int i = x; i > 0; i -= (i & -i)) {
            ans += bit[i].order_of_key(mk(mk(y + 1, 0), -1));
      }
      return ans;
}

signed main()
{
      ios_base::sync_with_stdio(false);
      cin.tie(nullptr);

      #ifndef ONLINE_JUDGE
          freopen("in.txt", "r", stdin);
      #endif // ONLINE_JUDGE
      
      int n, area;
      cin >> n >> area;
      vector <pii> point;
      for (int i = 1; i <= n; i++) {
            int x, y;
            cin >> x >> y;
            point.push_back(mk(x, y));
      }
      sort(point.begin(), point.end());
      for (pii p : point) {
            Insert(p.first, p.second);
      }
      int maxPoints = 0;
      for (int i = 0; i < n; i++) {
            int x = point[i].first;
            int y = min(area / x, N);
            int points = query(x, y);
            maxPoints = max(maxPoints, points);
      }
      cout << maxPoints << endl;
}
