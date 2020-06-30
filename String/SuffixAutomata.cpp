struct State {
      int len;
      int link;
      int pos;
      int w;
      int v;
      long long occ;
      long long word;
      map <char, int> child;
      vector <int> dag;

      State() {
            len = 0;
            link = -1;
            pos = -1;
            w = 1e9;
            v = 0;
            occ = 0;
            word = 0;
            child.clear();
            dag.clear();
      }
};

struct SuffixAutomata {
      const int Max = 1e6 + 5;

      vector <State> st;
      vector <long long> dsub;
      vector <long long> dsub_len;
      int sz;
      int last;

      void init() {
            sz = 0;
            last = 0;
            st.resize(Max, State());
            dsub.resize(Max, -1);
            dsub_len.resize(Max, -1);
      }
      long long sz_extend(char ch, int pos) {
            long long sum = 0;
            int cur = ++sz;
            int l;
            int r;
            st[cur].len = st[last].len + 1;
            st[cur].pos = pos;
            int p;
            for (p = last; p != -1 and st[p].child.count(ch) == 0; p = st[p].link) {
                  st[p].child[ch] = cur;
            }
            if (p == -1) {
                  st[cur].link = 0;
            }
            else {
                  int q = st[p].child[ch];
                  if (st[p].len + 1 == st[q].len) {
                        st[cur].link = q;
                  }
                  else {
                        int clone = ++sz;
                        st[clone].len = st[p].len + 1;
                        st[clone].child = st[q].child;
                        st[clone].link = st[q].link;
                        st[clone].pos = st[q].pos;
                        st[clone].w = 1e9;
                        for ( ; p != -1 and st[p].child[ch] == q; p = st[p].link) {
                              st[p].child[ch] = clone;
                        }
                        l = st[ st[q].link ].len;
                        r = st[q].len;
                        assert(l + 1 <= r);
//                        range_update(l + 1, r, -1);
                        sum -= (r - l);

                        st[q].link = st[cur].link = clone;

                        l = st[ st[q].link ].len;
                        r = st[q].len;
                        assert(l + 1 <= r);
//                        range_update(l + 1, r, 1);
                        sum += (r - l);

                        l = st[ st[clone].link ].len;
                        r = st[clone].len;
                        assert(l + 1 <= r);
//                        range_update(l, r, 1);
                        sum += (r - l);
                  }
            }
            l = st[ st[cur].link ].len;
            r = st[cur].len;
            assert(l + 1 <= r);
//            range_update(l + 1, r, 1);
            sum += (r - l);
            last = cur;
            return sum;
      }
      void make_dag() {
            for (int v = last; v >= 0; v--) {
                  int u = st[v].link;
                  st[u].dag.push_back(v);
            }
      }
      long long distinct_sub_string(int u = 0) {
            long long &ret = dsub[u];
            if (~ret) {
                  return ret;
            }
            ret = 1;
            for (auto it : st[u].child) {
                  ret += distinct_sub_string(it.second);
            }
            return ret;
      }
      long long distinct_sub_string_len(int u = 0) { // calculate distinct_sub_string() first
            long long &ret = dsub_len[u];
            if (~ret) {
                  return ret;
            }
            ret = 0;
            for (auto it : st[u].child) {
                  ret += distinct_sub_string_len(it.second) + dsub[it.second];
            }
            return ret;
      }
      void klex(int u, int k, string &s) {
            if (k == 0) {
                  return;
            }
            for (auto it : st[u].child) {
                  int tsub = dsub[it.second];
                  if (tsub < k) {
                        k -= tsub;
                  }
                  else {
                        s.push_back(it.first);
                        klex(it.second, k - 1, s);
                        return;
                  }
            }
      }
      void all_terminal() {
            int cur = last;
            while (cur > 0) {
                  st[cur].occ += 1;
                  cur = st[cur].link;
            }
      }
      void dfs(int u = 0) {
            if (st[u].word) {
                  return;
            }
            for (auto it : st[u].child) {
                  int v = it.second;
                  dfs(v);
                  st[u].occ += st[v].occ;
                  st[u].word += st[v].word;
            }
            st[u].word += st[u].occ;
      }
      void klex_all(int u, int k, string &s) {
            if (k <= 0) {
                  return;
            }
            for (auto it : st[u].child) {
                  char ch = it.first;
                  int v = it.second;
                  if (st[v].word < k) {
                        k -= st[v].word;
                  }
                  else {
                        s.push_back(ch);
                        klex_all(v, k - st[v].occ, s);
                        return;
                  }
            }
      }
      void lcs(string &t) {
            int v = 0;
            int l = 0;
            int len = t.size();
            for (int i = 0; i < len; i++) {
                  char ch = t[i];
                  while (v and st[v].child.count(ch) == 0) {
                        v = st[v].link;
                        l = st[v].len;
                  }
                  if (st[v].child.count(ch)) {
                        v = st[v].child[ch];
                        l++;
                  }
                  st[v].v = max(st[v].v, l);
            }
            for (int i = 1; i <= sz; i++) {
                  MAX(st[ st[i].link ].v, st[i].v);
            }
            for (int i = 0; i <= sz; i++) {
                  MIN(st[i].w, st[i].v);
                  st[i].v = 0;
            }
      }
      int longest_common_substring(vector <string> &vec) {
            int maxlen = 0;
            int id = 0;
            int n = vec.size();
            for (int i = 0; i < n; i++) {
                  int len = vec[i].size();
                  if (MAX(maxlen, len)) {
                        id = i;
                  }
            }
            init();
            for (int i = 0; i < vec[id].size(); i++) {
                  sz_extend(vec[id][i], i);
            }
            for (int i = 0; i < n; i++) {
                  if (i == id) {
                        continue;
                  }
                  lcs(vec[i]);
            }
            int best = 0;
            int bestPos = -1;
            for (int i = 0; i <= sz; i++) {
                  int len = min(st[i].len, st[i].w);
                  if (MAX(best, len)) {
                        bestPos = st[i].pos;
                  }
            }
//            string res = vec[id].substr(bestPos, best);
//            debug(res);
            return best;
      }
};
