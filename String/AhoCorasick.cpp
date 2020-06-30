/*
  Aho-Corasick Algorithm for multiple pattern searching
  Never use "patternIndices" if it is not necessary.

  Test: https://codeforces.com/edu/course/2/lesson/2/3/practice/contest/269118/problem/B
*/

struct Aho {
      const int let = 26;
      const int Max = 6e5 + 5;

      vector < vector <int> > child;
      vector <int> End;
      int sz;
      vector <int> Num;
      vector <int> backPoint;
      vector <int> created;
      vector <int> occ;
      vector <int> vis;
      vector < vector <int> > out;
      vector < vector <int> > patternIndices;
      vector < vector <int> > occur;

      void init() {
            sz = 0;
            child.resize(let, vector <int> (Max));
            End.resize(Max);
            Num.resize(Max);
            backPoint.resize(Max);
            created.reserve(Max);
            occ.resize(Max);
            vis.resize(Max);
            out.resize(Max);
            patternIndices.resize(Max);
            occur.resize(Max);
      }
      void insert_pattern(const string &pat, const int id) {
            int v = 0;
            for (char ch : pat) {
                  int val = ch - 'a';
                  if (created[ child[val][v] ] == 0) {
                        ++sz;
                        child[val][v] = sz;
                        created[sz] = 1;
                  }
                  v = child[val][v];
            }
            Num[v]++;
//            patternIndices[v].push_back(id);
      }
      void build_failure() {
            queue <int> pq;
            int v = 0;
            for (int i = 0; i < let; i++) {
                  if (child[i][v]) {
                        pq.push(child[i][v]);
                        backPoint[ child[i][v] ] = v;
                        out[v].push_back(child[i][v]);
                  }
            }
            while (pq.size()) {
                  int u = pq.front(); pq.pop();
                  for (int i = 0; i < let; i++) {
                        int v = child[i][u];
                        if (v == 0) {
                              continue;
                        }
                        int w = backPoint[u];
                        while (w and child[i][w] == 0) {
                              w = backPoint[w];
                        }
                        backPoint[v] = child[i][w];
                        out[ backPoint[v] ].push_back(v);
                        Num[v] += Num[ backPoint[v] ];
//                          for (int p : patternIndices[ backPoint[v] ]) {
//                              patternIndices[v].push_back(p);
//                        }
                        pq.push(v);
                  }
            }
      }
      int insert_text(const string &text) {
            int v = 0;
            int ans = 0;
            int len = text.size();
            for (int i = 0; i < len; i++) {
                  int val = text[i] - 'a';
                  while (v and child[val][v] == 0) {
                        v = backPoint[v];
                  }
                  v = child[val][v];
                  ans += Num[v];
                  occ[v]++;
//                  for (int p : patternIndices[v]) {
//                        occur[p].push_back(i);
//                  }
            }
            return ans;
      }
      int dfs(int u = 0) {
            if (vis[u]) {
                  return occ[u];
            }
            vis[u] = 1;
            for (int v : out[u]) {
                  occ[u] += dfs(v);
            }
            return occ[u];
      }
      int query(const string &pat) {
            int v = 0;
            for (char ch : pat) {
                  int val = ch - 'a';
                  v = child[val][v];
            }
            return occ[v];
      }
      int query(const int id) {
            return occur[id].size();
      }
};

signed main()
{
      string text;
      cin >> text;
      int q;
      cin >> q;
      vector <string> pats(q);
      Aho aho;
      aho.init();
      for (string &s : pats) {
            cin >> s;
            aho.insert_pattern(s, 0);
      }
      aho.build_failure();
      aho.insert_text(text);
      aho.dfs();
      for (string s : pats) {
            int cnt = aho.query(s);
            cout << cnt << endl;
      }
}
