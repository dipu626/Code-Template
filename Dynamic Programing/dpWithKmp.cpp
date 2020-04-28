#include "bits/stdc++.h"

using namespace std;

#define ll          long long int
#define endl        '\n'

static const int maxn = 200 + 5;
static const ll  mod = 1e9 + 7;

vector <int> LPS(string &pat) {
      int len = pat.size();
      int i = 1;
      int j = 0;
      vector <int> lps;
      lps.emplace_back(0);
      while (i < len) {
            if (pat[i] == pat[j]) {
                  i++;
                  j++;
                  lps.emplace_back(j);
            }
            else {
                  if (j) {
                        j = lps[j - 1];
                  }
                  else {
                        lps.emplace_back(0);
                        i++;
                  }
            }
      }
      return lps;
}

vector <int> lps;
string pat;

int kmp(int id, char brac) {
      while (id > 0 && brac != pat[id]) {
            id = lps[id-1];
      }
      if (brac == pat[id]) {
            ++id;
      }
      return id;
}

ll dp[maxn][maxn][maxn];
int n;

ll solve(int pos, int open, int found)
{
      if (pos >= 2*n) {
            return (open == 0 && found >= pat.size());
      }
      ll &ret = dp[pos][open][found];
      if (~ret) return ret;
      ll choice1 = 0;
      ll choice2 = 0;
      {
            int fnd = found;
            if (fnd < pat.size()) {
                  fnd = kmp(fnd, '(');
            }
            choice1 = (choice1 + solve(pos + 1, open + 1, fnd)) % mod;
      }
      {
            if (open) {
                  int fnd = found;
                  if (fnd < pat.size()) {
                        fnd = kmp(found, ')');
                  }
                  choice2 = (choice2 + solve(pos + 1, open - 1, fnd)) % mod;
            }
      }
      return ret = (choice1 + choice2) % mod;
}

signed main()
{
      ios_base::sync_with_stdio(false);
      cin.tie(nullptr);

      #ifndef ONLINE_JUDGE
            freopen("in.txt", "r", stdin);
      #endif // ONLINE_JUDGE

      cin >> n >> pat;
      lps = LPS(pat);
      memset(dp, -1, sizeof dp);
      cout << solve(0, 0, 0);
}
