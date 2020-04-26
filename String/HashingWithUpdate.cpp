#include "bits/stdc++.h"  
  
using namespace std;  
  
static const int maxn = 2e5 + 5;  
static const long long mod = 1e9 + 123;  
  
struct SegmentTree  
{  
      long long x;  
      unsigned long long y;  
      SegmentTree(long long x = 0, unsigned long long y = 0) : x(x), y(y) {}  
  
      void assignLeaf(long long xx, unsigned long long yy)  
      {  
            x = xx;  
            y = yy;  
      }  
      void marge(const SegmentTree &lchild, const SegmentTree &rchild)  
      {  
            x = (lchild.x + rchild.x) % mod;  
            y = lchild.y + rchild.y;  
      }  
} Tree[maxn * 4];  
  
void update(int node, int a, int b, int pos, long long x, unsigned long long y)  
{  
      if (a > pos or b < pos) return;  
      if (a >= pos and b <= pos)  
      {  
            Tree[node].assignLeaf(x, y);  
            return;  
      }  
      int lft = node * 2;  
      int rgt = lft + 1;  
      int mid = (a + b) / 2;  
      update(lft, a, mid, pos, x, y);  
      update(rgt, mid + 1, b, pos, x, y);  
      Tree[node].marge(Tree[lft], Tree[rgt]);  
}  
  
SegmentTree query(int node, int a, int b, int i, int j)  
{  
      if (a > j or b < i) return SegmentTree();  
      if (a >= i and b <= j) return Tree[node];  
      int lft = node * 2;  
      int rgt = lft + 1;  
      int mid = (a + b) / 2;  
      SegmentTree p = query(lft, a, mid, i, j);  
      SegmentTree q = query(rgt, mid + 1, b, i, j);  
      SegmentTree res;  
      res.marge(p, q);  
      return res;  
}  
  
int gen_base(const int before, const int after)  
{  
      auto seed = chrono::high_resolution_clock::now().time_since_epoch().count();  
      mt19937 mt_rand(seed);  
      int base = uniform_int_distribution <int> (before, after)(mt_rand);  
      return base % 2 == 0 ? base - 1 : base;  
}  
  
long long pow1[maxn];  
unsigned long long pow2[maxn];  
int base;  
  
void preCalc()  
{  
      pow1[0] = 1;  
      pow2[0] = 1;  
      for (int i = 1; i < maxn; i++)  
      {  
            pow1[i] = (1LL * base * pow1[i - 1]) % mod;  
            pow2[i] = pow2[i - 1] * base;  
      }  
}  
  
signed main()  
{  
      ios_base::sync_with_stdio(false);  
      cin.tie(nullptr);  
  
      #ifndef ONLINE_JUDGE  
            freopen("in.txt", "r", stdin);  
      #endif // ONLINE_JUDGE  
  
      base = gen_base(256, mod);  
      preCalc();  
  
      int tc;  
      cin >> tc;  
      for (int tcase = 1; tcase <= tc; tcase++)  
      {  
            int n, q;  
            cin >> n >> q;  
            string s;  
            cin >> s;  
            for (int i = 0; i < n; i++)  
            {  
                  long long x = (1LL * s[i] * pow1[i]) % mod;  
                  long long y = s[i] * pow2[i];  
                  update(1, 1, n, i + 1, x, y);  
            }  
            cout << "Case " << tcase << ":\n";  
            int mxPow = n;  
            while (q--)  
            {  
                  int type;  
                  cin >> type;  
                  if (type == 0)  
                  {  
                        int pos;  
                        cin >> pos;  
                        if (s[pos] == '1') s[pos] = '0';  
                        else s[pos] = '1';  
                        long long x = (1LL * s[pos] * pow1[pos]) % mod;  
                        long long y = s[pos] * pow2[pos];  
                        update(1, 1, n, pos + 1, x, y);  
                  }  
                  else  
                  {  
                        int i, j, len;  
                        cin >> i >> j >> len;  
                        SegmentTree tree1;  
                        tree1 = query(1, 1, n, i + 1, i + len);  
                        if (tree1.x < 0) tree1.x += mod;  
                        if (mxPow != 0)  
                        {  
                              tree1.x = tree1.x * pow1[mxPow - (i + len - 1)] % mod;  
                              tree1.y = tree1.y * pow2[mxPow - (i + len - 1)];  
                        }  
                        SegmentTree tree2;  
                        tree2 = query(1, 1, n, j + 1, j + len);  
                        if (tree2.x < 0) tree2.x += mod;  
                        if (mxPow != 0)  
                        {  
                              tree2.x = tree2.x * pow1[mxPow - (j + len - 1)] % mod;  
                              tree2.y = tree2.y * pow2[mxPow - (j + len - 1)];  
                        }  
                        if (tree1.x == tree2.x and tree1.y == tree2.y) cout << 1 << '\n';
                        else cout << 0 << '\n';  
                  }  
            }  
      }  
}
