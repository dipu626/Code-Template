/*
  Problem : F - Range Set Query
  OJ      : atcoder.jp
  
  Statement : We have N colored balls arranged in a row from left to right; the color of the i-th ball from the left is Ci
              You are given Q queries. The i-th query is as follows: how many different colors do the L-th through R-th balls from the left have?
              
  Complexity : O((n + q) * sqrt(n)), k = sqrt(n)
*/

struct Mo {
      int l, r, id;
      Mo(int l = 0, int r = 0, int id = 0)
            : l(l), r(r), id(id) {}

      friend bool operator < (Mo p, Mo q) {
            int pb = p.l / block;
            int qb = q.l / block;
            if (pb != qb) {
                  return p.l < q.l;
            }
            return (p.r < q.r) ^ (p.l / block % 2);
      }
} queries[maxn];

int arr[maxn];
int fre[maxn];

int l = 1, r = 0, ans[maxn];
int difColor;

void add(int pos) {
      int x = arr[pos];
      if (fre[x] == 0) {
            difColor++;
      }
      fre[x]++;
}

void remov(int pos) {
      int x = arr[pos];
      if (fre[x] == 1) {
            difColor--;
      }
      fre[x]--;
}

void solve() {
      int n, q;
      cin >> n >> q;
      for (int i = 1; i <= n; i++) {
            cin >> arr[i];
      }
      for (int i = 0; i < q; i++) {
            int a, b;
            cin >> a >> b;
            queries[i] = {a, b, i};
      }
      sort(queries, queries + q);
      for (int i = 0; i < q; i++) {
            int L = queries[i].l;
            int R = queries[i].r;
            int ID = queries[i].id;
            while (l > L)   add(--l);
            while (r < R)   add(++r);
            while (l < L)   remov(l++);
            while (r > R)   remov(r--);
            ans[ID] = difColor;
      }
      for (int i = 0; i < q; i++) {
            cout << ans[i] << endl;
      }
}
