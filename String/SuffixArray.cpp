static const int maxn = 2e6 + 5;
static const int logn = 20;

int p[maxn];
int pn[maxn];
int c[logn][maxn];
int cn[maxn];
int cnt[maxn];

void sort_cyclic_shifts(string &s) {
      int n = s.size();
      memset(cnt, 0, sizeof cnt);
      for (int i = 0; i < n; i++) {
            cnt[ s[i] ]++;
      }
      for (int i = 1; i < 256; i++) {
            cnt[i] += cnt[i - 1];
      }
      for (int i = 0; i < n; i++) {
            p[ --cnt[ s[i] ] ] = i;
      }
      int classes = 1;
      for (int i = 0; i < n; i++) {
            if (i && s[ p[i] ] != s[ p[i - 1] ]) {
                  classes++;
            }
            c[0][ p[i] ] = classes - 1;
      }
      for (int k = 0; (1 << k) < n; k++) {
            for (int i = 0; i < n; i++) {
                  pn[i] = p[i] - (1 << k);
                  if (pn[i] < 0) {
                        pn[i] += n;
                  }
            }
            fill(cnt, cnt + classes, 0);
            for (int i = 0; i < n; i++) {
                  cnt[ c[k][ pn[i] ] ]++;
            }
            for (int i = 1; i < classes; i++) {
                  cnt[i] += cnt[i - 1];
            }
            for (int i = n - 1; i >= 0; i--) {
                  p[ --cnt[ c[k][ pn[i] ] ] ] = pn[i];
            }
            classes = 1;
            cn[ p[0] ] = 0;
            pair <int, int> x;
            pair <int, int> y;
            for (int i = 1; i < n; i++) {
                  x = {c[k][ p[i] ], c[k][(p[i] + (1 << k)) % n]};
                  y = {c[k][ p[i - 1] ], c[k][(p[i - 1] + (1 << k)) % n]};
                  if (x != y) {
                        classes++;
                  }
                  cn[ p[i] ] = classes - 1;
            }
            for (int i = 0; i < n; i++) {
                  c[k + 1][i] = cn[i];
            }
      }
}

vector <int> suffix_array_construction(string s) {
      s += "$";
      sort_cyclic_shifts(s);
      vector <int> sorted_shifts;
      int n = s.size();
      for (int i = 1; i < s.size(); i++) {
            sorted_shifts.push_back(p[i]);
      }
      return sorted_shifts;
}

// compare two equal length substring in O(1)
int compare(int i, int j, int substr_len, int n) {
      // i = start index of first index
      // j = start index of second index
      // substr_len = length of sub-string
      // n = length of original string
      int k = __lg(substr_len);
      pair <int, int> a = make_pair(c[k][i], c[k][(i + substr_len - (1 << k)) % n]);
      pair <int, int> b = make_pair(c[k][j], c[k][(j + substr_len - (1 << k)) % n]);
      return a == b ? 0 : a < b ? -1 : 1;
}

int longest_common_prefix(int i, int j) {
      int ans = 0;
      for (int k = logn - 1; k >= 0; k--) {
            if (c[k][i] == c[k][j]) {
                  ans += (1 << k);
                  i += (1 << k);
                  j += (1 << k);
            }
      }
      return ans;
}

vector <int> lcp_construction(string const &s, vector <int> const &suffix_array) {
      int n = s.size();
      vector <int> Rank(n, 0);
      for (int i = 0; i < n; i++) {
            Rank[ suffix_array[i] ] = i;
      }
      int k = 0;
      vector <int> lcp(n - 1, 0);
      for (int i = 0; i < n; i++) {
            if (Rank[i] == n - 1) {
                  k = 0;
                  continue;
            }
            int j = suffix_array[ Rank[i] + 1 ];
            while (i + k < n && j + k < n && s[i + k] == s[j + k]) {
                  k++;
            }
            lcp[ Rank[i] ] = k;
            if (k) {
                  --k;
            }
      }
      return lcp;
}
