static const int maxn = 3e5 + 5;
static const int logn = 20;

struct AhoCorasick {
      int sz;
      array <int, maxn> Num;
      array <int, maxn> backPoint;
      array < map <char, int>, maxn> child;

      void init() {
            assert(sz < maxn);
            for (int i = 0; i <= sz; i++) {
                  Num[i] = 0;
                  backPoint[i] = -1;
                  child[i].clear();
            }
            sz = 0;
      }
      AhoCorasick() {
            init();
      }
      void insertPattern(const string &pat) {
            int v = 0;
            for (char ch : pat) {
                  if (child[v].count(ch) == 0) {
                        child[v][ch] = ++sz;
                  }
                  v = child[v][ch];
            }
            Num[v]++;
      }
      void findBackPointer() {
            queue <int> pq;
            pq.emplace(0);
            while (pq.size()) {
                  int u = pq.front();
                  pq.pop();
                  for (auto it : child[u]) {
                        int v = it.second;
                        char ch = it.first;
                        int w = backPoint[u];
                        while (w != -1 && child[w].count(ch) == 0) {
                              w = backPoint[w];
                        }
                        if (w == -1) {
                              backPoint[v] = 0;
                        }
                        else {
                              backPoint[v] = child[w][ch];
                        }
                        Num[v] += Num[ backPoint[v] ];
                        pq.emplace(v);
                  }
            }
      }
      int insertTextAndQuery(const string &text) {
            int v = 0;
            int ans = 0;
            for (char ch : text) {
                  while (v != -1 && child[v].count(ch) == 0) {
                        v = backPoint[v];
                  }
                  if (v == -1) {
                        v = 0;
                  }
                  else {
                        v = child[v][ch];
                  }
                  ans += Num[v];
            }
            return ans;
      }
};

struct AhoCorasickDynamic {
      vector <string> lst[logn];
      AhoCorasick aho[logn];

      void init() {
            for (int i = 0; i < logn; i++) {
                  lst[i].clear();
                  aho[i].init();
            }
      }
      AhoCorasickDynamic() {
            init();
      }
      void insertPattern(const string &pat) {
            int position = 0;
            for (int i = 0; i < logn; i++) {
                  if (lst[i].empty()) {
                        position = i;
                        break;
                  }
            }
            lst[position].emplace_back(pat);
            aho[position].insertPattern(pat);
            for (int i = 0; i < position; i++) {
                  aho[i].init();
                  for (string p : lst[i]) {
                        lst[position].emplace_back(p);
                        aho[position].insertPattern(p);
                  }
                  lst[i].clear();
            }
            aho[position].findBackPointer();
      }
      int query(const string &text) {
            int ans = 0;
            for (int i = 0; i < logn; i++) {
                  ans += aho[i].insertTextAndQuery(text);
            }
            return ans;
      }
};

AhoCorasickDynamic add;
AhoCorasickDynamic del;

signed main()
{
      ios_base::sync_with_stdio(false);
      cin.tie(nullptr);

      #ifndef ONLINE_JUDGE
          freopen("in.txt", "r", stdin);
      #endif // ONLINE_JUDGE

      int n;
      cin >> n;
      int type;
      string s;
      for (int i = 0; i < n; i++) {
            cin >> type >> s;
            if (type == 1) {
                  add.insertPattern(s);
            }
            else if (type == 2) {
                  del.insertPattern(s);
            }
            else {
                  cout << (add.query(s) - del.query(s)) << endl;
            }
      }

}
