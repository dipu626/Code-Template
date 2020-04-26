// Problem : https://codeforces.com/contest/813/problem/F 

#include "bits/stdc++.h"

using namespace std;

#define pii             pair <int, int>
#define mk              make_pair

static const int maxn = 3e5 + 5;

vector <pii> Tree[maxn * 4];

void update(int node, int a, int b, int i, int j, pii p)
{
      if (a > j or b < i) return;
      if (a >= i and b <= j) return void(Tree[node].push_back(p));
      int lchild = node * 2;
      int rchild = lchild + 1;
      int mid = (a + b) / 2;
      update(lchild, a, mid, i, j, p);
      update(rchild, mid + 1, b, i, j, p);
}

int par[maxn];
int sz[maxn];
int dist[maxn];
bool bipertite;
stack <int> st;

void makeSet()
{
      for (int i = 1; i < maxn; i++)
      {
            par[i] = i;
            sz[i] = 1;
            dist[i] = 0;
      }
}

pii findRep(int r)
{
      int d = 0;
      while (par[r] != r)
      {
            d += dist[r];
            r = par[r];
      }
      return mk(r, d);
}

void marge(int u, int v)
{
      if (bipertite == false) return;
      pii p = findRep(u);
      pii q = findRep(v);
      if (p.first == q.first)
      {
            int d = p.second + q.second;
            if (d % 2 == 0)
            {
                  bipertite = false;
                  st.push(-1);
            }
      }
      else
      {
            int x = p.first;
            int y = q.first;
            if (sz[x] > sz[y]) swap(x, y);
            par[x] = y;
            sz[y] += sz[x];
            dist[x] = p.second + q.second + 1;
            st.push(x);
      }
}

void rollback(int moment)
{
      while (st.size() > moment)
      {
            int curr = st.top(); st.pop();
            if (curr == -1)
            {
                  bipertite = true;
            }
            else
            {
                  sz[ par[curr] ] -= sz[curr];
                  dist[curr] = 0;
                  par[curr] = curr;
            }
      }
}

bool ans[maxn];

void dfs(int node, int a, int b)
{
      if (a > b) return;
      int moment = st.size();
      for (pii p : Tree[node]) marge(p.first, p.second);
      if (a == b)
      {
            ans[a] = bipertite;
      }
      else
      {
            int lchild = node * 2;
            int rchild = lchild + 1;
            int mid = (a + b) / 2;
            dfs(lchild, a, mid);
            dfs(rchild, mid + 1, b);
      }
      rollback(moment);
}

map <pii, int> in;
vector <int> queries;

signed main()
{
      ios_base::sync_with_stdio(false);
      cin.tie(nullptr);
      cout.tie(nullptr);

      #ifndef ONLINE_JUDGE
            freopen("in.txt", "r", stdin);
      #endif // ONLINE_JUDGE

      int n, q;
      cin >> n >> q;
      for (int i = 1; i <= q; i++)
      {
            int a, b;
            cin >> a >> b;
            assert(a < b);
            if (!in.count(mk(a, b)))
            {
                  in[mk(a, b)] = i;
            }
            else
            {
                  int l = in[mk(a, b)];
                  int r = i - 1;
                  update(1, 1, q, l, r, mk(a, b));
                  in.erase(mk(a, b));
            }
            queries.push_back(i);
      }
      for (auto it : in)
      {
            int l = it.second;
            int r = q;
            int a = it.first.first;
            int b = it.first.second;
            update(1, 1, q, l, r, mk(a, b));
      }
      makeSet();
      bipertite = true;
      dfs(1, 1, q);
      for (int p : queries) cout << (ans[p] ? "YES" : "NO") << '\n';
}
