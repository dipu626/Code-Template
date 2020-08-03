/*
  Problem : SPOJ - XXXXXXXX Sum of Distinct Numbers
  OJ      : SPOJ
  
  Statement : You are given N numbers. You have to perform two kinds of operations:
              U x y - x-th number becomes equal to y.
              Q x y - calculate the sum of distinct numbers from x-th to y-th. It means that the sum for the set {1, 2, 3, 2, 7} will be equal to 13 (1+2+3+7).

  Complexity : O(n ^ (5 / 3)), block = O(n ^ (2 / 3))
*/

struct Mo {
      int l, r, id, t;
      Mo(int l = 0, int r = 0, int id = 0, int t = 0)
            : l(l), r(r), id(id), t(t) {}

      friend bool operator < (Mo p, Mo q) {
            int pl = p.l / block;
            int ql = q.l / block;
            int pr = p.r / block;
            int qr = q.r / block;
            if (pl == ql) {
                  if (pr == qr) {
                        return p.t < q.t;
                  }
                  return pr < qr;
            }
            return pl < ql;
      }
} queries[maxn];

struct Data {
      int pos;
      long long pre, now;
      Data(int pos = 0, long long pre = 0, long long now = 0)
            : pos(pos), pre(pre), now(now) {}
} updateData[maxn];

long long arr[maxn];
long long last[maxn];
long long ans[maxn];
long long fre[maxn];
long long rmp[maxn];
long long sum;

int l = 1, r = 0, t;

void add(int pos) {
      long long num = arr[pos];
      if (fre[num] == 0) {
            sum += rmp[num];
      }
      fre[num]++;
}

void remov(int pos) {
      long long num = arr[pos];
      if (fre[num] == 1) {
            sum -= rmp[num];
      }
      fre[num]--;
}

void apply(int pos, long long val) {
      if (l <= pos && pos <= r) {
            remov(pos);
            arr[pos] = val;
            add(pos);
      }
      else {
            arr[pos] = val;
      }
}

void solve() {
      int n;
      cin >> n;
      map <long long, long long> mp;
      for (int i = 1; i <= n; i++) {
            cin >> arr[i];
            last[i] = arr[i];
            mp[ arr[i] ];
      }
      int ptr = 0;
      for (auto &it : mp) {
            it.second = ++ptr;
            rmp[ptr] = it.first;
      }
      for (int i = 1; i <= n; i++) {
            last[i] = arr[i] = mp[ arr[i] ];
      }
      int q;
      cin >> q;
      int uptr = 0;
      int qptr = 0;
      for (int i = 0; i < q; i++) {
            char type;
            cin >> type;
            if (type == 'U') {     // update
                  int pos;
                  long long value;
                  cin >> pos >> value;
                  if (mp.find(value) == mp.end()) {
                        mp[value] = ++ptr;
                        rmp[ptr] = value;
                  }
                  long long tempValue = mp[value];
                  updateData[++uptr] = {pos, last[pos], tempValue};
                  last[pos] = tempValue;
            }
            else {
                  int a, b;
                  cin >> a >> b;
                  queries[qptr++] = {a, b, qptr, uptr};
            }
      }
      sort(queries, queries + qptr);
      l = 1;
      r = 0;
      t = 0;
      sum = 0;
      for (int i = 0; i < qptr; i++) {
            int L = queries[i].l;
            int R = queries[i].r;
            int T = queries[i].t;
            while (t < T) {
                  t++;
                  apply(updateData[t].pos, updateData[t].now);
            }
            while (t > T) {
                  apply(updateData[t].pos, updateData[t].pre);
                  t--;
            }
            while (l > L) add(--l);
            while (r < R) add(++r);
            while (l < L) remov(l++);
            while (r > R) remov(r--);
            ans[ queries[i].id ] = sum;
      }
      for (int i = 0; i < qptr; i++) {
            cout << ans[i] << endl;
      }
}
